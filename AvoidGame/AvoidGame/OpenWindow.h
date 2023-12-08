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
	// ������ ��ü ����

	Event Event; // �̺�Ʈ Ŭ���� ���� ����

	/*	�̺�Ʈ ����
	*	Window.
		����
	*/

	//������ â�� �������� ���α׷� ���� ���� �ʵ���
	while (Window.isOpen()) 
	{	//�̺�Ʈ�߻� ����
		while (Window.pollEvent(Event)) //��½� 0�� ��� ���, �Է½� ������ �ٲ�� pollevent ���� event�� ����.
		{	//�̺�Ʈ ���� �Ǵ�
			switch (Event.type) 
			{	//����
				case Event::Closed:
				Window.close();
				break; //case �������� �ݺ����� �ݱ�

				case Event::KeyPressed:	//�ƹ�Ű �Է�
					if(Event.key.code == Keyboard::Escape) // esc �Է��ϸ�
					Window.close();		// ������â �ݱ�
					break; 
			
			
			}
			
			

		}
		//clear
		//Window.clear(Color::Cyan); //ȭ���� ������� ĥ��, 
		Window.clear(Color(50,50,50,255));//clear(Color(r,g,b,a)) a=0(����)~255(������)
		//�پ��� ���� ���ϴ°�� rgb(��)a(����) �Ű������� ��������, 8��Ʈ(0~255)*3 = 24bit 
		//display
		Window.display(); //Ŭ����� ������ ���� ǥ������

	}
}

/*
	�̺�Ʈ (Event) : �߻��� ��� 
	> ����Ʈ����, ���ø����̼��� ���°� ��ȭ�� : �����

	- Interface ��ġ�� ���õ� �̺�Ʈ : Ű����, ���콺, ��ġ��ũ��
	Ű���� �̺�Ʈ : Ű �Է�(press) ������ Ű ������ if�� ����
	���콺 �̺�Ʈ : Ŭ��(press ������,release ����), �ٽ�ũ��, ����Ŭ��, ������, �巡��(press + move)
	��ġ ��ũ�� : ��ġ, ��������(�ѱ��) , ��ġ(���̱�, ���̱�)
	Interface ��ġ�� ���þ��� �̺�Ʈ
	�ε� �̺�Ʈ: �����ͳ� ����Ʈ������ ȭ�� ���� ��� ��� ȭ�鿡 ������� �߻��Ǵ� �̺�Ʈ

	�̺�Ʈ �߻��� �̺�Ʈ ���� > �ش� �̺�Ʈ�� ������ ����

	Event Listening : �̺�Ʈ ����
	Event Handling : ������ �̺�Ʈ�� ���ؼ� ������ ����
,

*/