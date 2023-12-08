#include <iostream>
#include<sfml/Audio.hpp>
#include<sfml/Graphics.hpp>
#include<sfml/Network.hpp>
#include<sfml/System.hpp>
#include<sfml/Window.hpp>

#include"OpenWindow.h"
#include"Game.h"

int main()
{   
    //랜덤값 사용 시작 : 초기값 설정
    //time 값 사용: 실행할때 마다 초기값 달라짐
    srand(time(NULL));

    //그래픽 윈도우 창 띄우기
    // OpenWindow();
    
    //게임클래스의 avoid 변수 선언
    Game Avoid;
    
    //게임루프
    while (Avoid.Running()) 
    {   
        //update, 변경값 전달
        Avoid.Update();

        //render,결과값 표현
        Avoid.Render();
        
   
    }

}
