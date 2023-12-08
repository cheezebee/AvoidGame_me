#include<sfml/Audio.hpp>
#include<sfml/Graphics.hpp>
#include<sfml/Network.hpp>
#include<sfml/System.hpp>
#include<sfml/Window.hpp>

#include <iostream>
using namespace sf;

void OpenWindow()
{
	RenderWindow Window(VideoMode(1280, 720), "Avoid Game Test", Style::Titlebar | Style::Close);
	// 윈도우 객체 선언

	Event Event; // 이벤트 클래스 변수 선언

	/*	이벤트 감지
	*	Window.
		동작
	*/

	//윈도우 창이 떠있을대 프로그램 종료 되지 않도록
	while (Window.isOpen()) 
	{	//이벤트발생 감지
		while (Window.pollEvent(Event)) //출력시 0이 계속 출력, 입력시 참으로 바뀌어 pollevent 값이 event로 대입.
		{	//이벤트 종류 판단
			switch (Event.type) 
			{	//동작
				case Event::Closed:
				Window.close();
				break; //case 마지막에 반복실행 닫기

				case Event::KeyPressed:	//아무키 입력
					if(Event.key.code == Keyboard::Escape) // esc 입력하면
					Window.close();		// 윈도우창 닫기
					break; 
			
			
			}
			
			

		}
		//clear
		//Window.clear(Color::Cyan); //화면을 흰색으로 칠함, 
		Window.clear(Color(50,50,50,255));//clear(Color(r,g,b,a)) a=0(투명)~255(불투명)
		//다양한 색을 원하는경우 rgb(색)a(투명도) 매개변수로 구현가능, 8비트(0~255)*3 = 24bit 
		//display
		Window.display(); //클리어에서 지정한 색을 표시해줌

	}
}

/*
	이벤트 (Event) : 발생된 사건 
	> 소프트웨어, 어플리케이션의 상태가 변화됨 : 사용자

	- Interface 장치와 관련된 이벤트 : 키보드, 마우스, 터치스크린
	키보드 이벤트 : 키 입력(press) 각각의 키 내용을 if로 구분
	마우스 이벤트 : 클릭(press 누르기,release 때기), 휠스크롤, 더블클릭, 움직임, 드래그(press + move)
	터치 스크린 : 터치, 스와이프(넘기기) , 핀치(늘이기, 줄이기)
	Interface 장치와 관련없는 이벤트
	로딩 이벤트: 데이터나 소프트웨어의 화면 구성 요소 모두 화면에 띄워지면 발생되는 이벤트

	이벤트 발생시 이벤트 감지 > 해당 이벤트에 적절한 동작

	Event Listening : 이벤트 감지
	Event Handling : 감지된 이벤트에 대해서 적절한 동작
,

*/