//"open window"의 정적 생성을 포인터를 활용하여 동적 생성을 하는 과정


//c++ lib
#include <iostream>
#include <vector> // 집합데이터 사용
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
	vector<RectangleShape> EnemyArray;//벡터타입 RectangleShape가 행열 형태로 유동적으로 생성

	int EnemyMax;		//적 최대 생성수
	float IntervalMax;	//적 생성 간격
	float IntervalStart;//적 생성 시작

	//point
	int point = 0;

	//font
	Font Font;

	//text, 
	Text PointText;
	Text GameOverText;

	bool GameOverState;
public:
	//동작흐름 구분
	
	//stratup
	Game();
	void InitWindowPointer();
	void InitWindow();
	
	//update
	//렌더 윈도우에 접근할 함수 만들기
	const bool Running() const;
	void EventHandler();
	void Update();

	//render
	void Render();
	
	//shut down
	~Game();
	void DeleteWiondow();
	
	/*
		element(구성요소)
	*/

	//player
	void InitPlayer();
	void UpdatePlayer();

	//Enemy
	void InitEnemy();
	void InitSpawn(); //스폰값 초기화
	void SpawnEnemy();
	void UpdateEnemy();

	//Collision Check
	void CollisionCheck();
	
	//font
	void InitFont();
	
	//text
	void InitPointText();	
	void UpdatePointText();	//점수누적갱신

	void InitGameOverText();
	void PrintGameOverText();
};