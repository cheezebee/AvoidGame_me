//"open window"�� ���� ������ �����͸� Ȱ���Ͽ� ���� ������ �ϴ� ����


//c++ lib
#include <iostream>
#include <vector> // ���յ����� ���
#include <sstream>


//sfml
#include<sfml/Audio.hpp>
#include<sfml/Graphics.hpp>
#include<sfml/Network.hpp>
#include<sfml/System.hpp>
#include<sfml/Window.hpp>



using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow* Window;
	Event Event;
	
	//player
	CircleShape Player;
	
	//Enemy
	RectangleShape Enemy;
	vector<RectangleShape> EnemyArray;//����Ÿ�� RectangleShape�� �࿭ ���·� ���������� ����

	int EnemyMax;		//�� �ִ� ������
	float IntervalMax;	//�� ���� ����
	float IntervalStart;//�� ���� ����

	//point
	int point = 0;

	//font
	Font Font;

	//text, 
	Text PointText;
	Text GameOverText;

	bool GameOverState;
public:
	//�����帧 ����
	
	//stratup
	Game();
	void InitWindowPointer();
	void InitWindow();
	
	//update
	//���� �����쿡 ������ �Լ� �����
	const bool Running() const;
	void EventHandler();
	void Update();

	//render
	void Render();
	
	//shut down
	~Game();
	void DeleteWiondow();
	
	/*
		element(�������)
	*/

	//player
	void InitPlayer();
	void UpdatePlayer();

	//Enemy
	void InitEnemy();
	void InitSpawn(); //������ �ʱ�ȭ
	void SpawnEnemy();
	void UpdateEnemy();

	//Collision Check
	void CollisionCheck();
	
	//font
	void InitFont();
	
	//text
	void InitPointText();	
	void UpdatePointText();	//������������

	void InitGameOverText();
	void PrintGameOverText();
};