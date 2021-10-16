#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "snake_game.h"

// 생성자()
//
SnakeGame::SnakeGame()
{
    initialize();
}

// initialize()
// ... 먹이 위치와 점수를 초기화한다.
//
void SnakeGame::initialize()
{
    food_position_.X = 0;
    food_position_.Y = 0;

    score_ = 0;
}

// start()
// ... 게임 플레이 전 여러가지를 처리한다.
//
ReturnCode SnakeGame::start()
{
    this->initialize();     // 점수와 먹이위치를 초기화한다.
    snake_.initialize();    // 뱀의 길이 및 위치를 초기화한다.

    display_.clear();
    display_.print_prompt("Do you want to play? (y/n) ");

    int key;
    do
    {
        key = _getch();
    } while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

    switch (key)
    {
    case 'y':
    case 'Y':
        make_food();
        display_.clear();
        display_.print_wall();
        display_.print_snake(snake_);
        display_.print_food(food_position_);
        return RETURN_SUCCESS;
    case 'n':
    case 'N':
        return RETURN_EXIT;
    default:
        return RETURN_UNKNOWN;
    }
}

// play()
// ... 실제로 게임을 실행시키고 이벤트를 처리한다.
//
ReturnCode SnakeGame::play()
{
    int key;
    while (FOREVER)
    {
        // 키보드 입력이 있는 경우를 처리한다.
        if (_kbhit())
        {
            key = _getch();
            if (key == 224)
            {
                // 방향키를 인식한 후 방향을 설정한다.
                key = _getch();
                switch (key)
                {
                case UP: case DOWN: case LEFT: case RIGHT:
                    snake_.set_direction((Keyboard)key);
                    break;
                default:
                    return RETURN_FATAL;
                }
            }
            else if (key == ESC)
            {
                // 일시정지 후 메뉴를 출력한다.
                switch (pause())
                {
                case RETURN_RESUME:
                    display_.clear();
                    display_.print_wall();
                    display_.print_snake(snake_);
                    display_.print_food(food_position_);
                    break;
                case RETURN_NEWGAME:
                    return RETURN_NEWGAME;
                case RETURN_STOP:
                    return RETURN_SUCCESS;
                case RETURN_EXIT:
                    return RETURN_EXIT;
                default:
                    return RETURN_UNKNOWN;
                }
            }
        }

        Sleep(GAME_SPEED);

        snake_.move();

        // 뱀이 벽에 부딪히면 게임이 끝난다.
        if (snake_.head().X == 0 || snake_.head().X == 79 ||
            snake_.head().Y == 0 || snake_.head().Y == 24)
        {
            return RETURN_STOP;
        }

        // 뱀이 자기 몸을 물었으면 게임이 끝난다.
        else if (snake_.is_bitten() == true)
        {
            return RETURN_STOP;
        }

        // 뱀이 먹이를 먹었다면 뱀의 길이를 하나 증가시키고 점수를 올린다.
        // 또 화면상의 먹이가 사라졌음을 표시한다.
        else if (snake_.head().X == food_position_.X &&
            snake_.head().Y == food_position_.Y)
        {
            putchar_at_xy(snake_.head().X, snake_.head().Y, 'O');
            score_++;
            food_position_.X = 0;
            food_position_.Y = 0;
        }

        // 뱀이 먹이를 먹은 것이 아니라면 일반적으로 진행한다.
        else
        {
            putchar_at_xy(snake_.head().X, snake_.head().Y, 'O');
            putchar_at_xy(snake_.tail().X, snake_.tail().Y, ' ');
            snake_.body().pop_back();
        }
        // 뱀이 먹이를 먹어 없앴다면 다시 만든다.
        if (is_no_food() == true)
        {
            make_food();
            display_.print_food(food_position_);
        }
    }

    return RETURN_SUCCESS;
}

// pause()
// ... 게임을 잠시 멈추고 메뉴를 보여준다.
//
ReturnCode SnakeGame::pause()
{
    display_.print_prompt("(R)esume, (N)ew game, (S)top, (E)xit ");

    int key;
    do
    {
        key = _getch();
    } while (key != 'r' && key != 'R' && key != 'n' && key != 'N' &&
        key != 's' && key != 'S' && key != 'e' && key != 'E');

    switch (key)
    {
    case 'r': case 'R':
        return RETURN_RESUME;
    case 'n': case 'N':
        return RETURN_NEWGAME;
    case 's': case 'S':
        return RETURN_STOP;
    case 'e': case 'E':
        return RETURN_EXIT;
    default:
        return RETURN_UNKNOWN;
    }
}

// stop()
//
ReturnCode SnakeGame::stop()
{
    display_.clear();

    // 획득한 점수를 출력한다.
    char msg[80];
    sprintf(msg, "Your score: %d ", score());
    display_.print_prompt(msg);

    // Enter키를 누르기 전까지 프로그램을 종료하지 않는다.
    go_to_xy(55-8, 24);
    printf("enter : quit, spacebar : newgame");

    int key;

    do {
        key = _getch();
    } while (key != ENTER && key != SPACEBAR);

    if (key == ENTER) {
        return RETURN_SUCCESS;
    }
    else if (key == SPACEBAR) {
        return RETURN_NEWGAME;
    }
        

    
}

// make_food()
// ... 먹이를 놓는다.
//
void SnakeGame::make_food()
{
    int x, y;

    srand((unsigned int)time(NULL));
    do
    {
        x = rand() % 77 + 1;    // 1 ~ 77
        y = rand() % 23 + 1;    // 1 ~ 23
    } while (is_valid_food_position(x, y) == false);

    food_position_.X = x;
    food_position_.Y = y;
}

// is_valid_food_position()
// ... 먹이를 놓을 수 있는 위치면 true, 아니면 false를 반환한다.
//
bool SnakeGame::is_valid_food_position(int x, int y)
{
    list<Position>::const_iterator iter = snake_.body().begin();
    while (iter != snake_.body().end())
    {
        if ((x == iter->X) && (y == iter->Y))
            return false;
        iter++;
    }

    return true;
}

// is_no_food()
// ... 게임화면에 먹이가 없으면 true, 있으면 false를 반환한다.
//
bool SnakeGame::is_no_food()
{
    if (food_position_.X == 0 || food_position_.Y == 0)
        return true;
    else
        return false;
}

// score()
//
const SnakeGame::ScoreType SnakeGame::score() const
{
    return score_;
}