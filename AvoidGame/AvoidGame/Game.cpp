#include "Game.h"

//startup
//생성자
Game::Game() //클래스game, 생성자 불러오기 
{
	//윈도우 초기화 및 생성 함수 가져오기
	this->InitWindowPointer();
	this->InitWindow();

	//player초기화
	this->InitPlayer();

	//enemy초기화
	this->InitEnemy();
	this->InitSpawn();

	//point 초기화
	this->point = 0;

	//font 초기화
	this->InitFont();

	//text 초기화
	this->InitPointText();
	
	//game over text 초기화
	this->InitGameOverText();

	//bool GameOverState 초기화
	this->GameOverState = false;
}
void Game::InitWindowPointer()
{	// 포인터 변수 최기화
	this->Window = nullptr;  
}
void Game::InitWindow()	//기능정의
{	//윈도우 동적생성, 왼쪽 상단 모서리부터 
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game Test", Style::Titlebar | Style::Close);	//동적생성
	//일정하게 반복 실행,(60프레임)
	this->Window->setFramerateLimit(60);
	
}

//update
const bool Game::Running() const
{
	return this->Window->isOpen();	//winow.isOpen = window(포인터)->isOpen
									//isOpen은 불데이터로 리턴됨...bool타입으로 사용
}
void Game::EventHandler()
{
	while (this->Window->pollEvent(Event)) //출력시 0이 계속 출력, 입력시 참으로 바뀌어 pollevent 값이 event로 대입.
	{	//이벤트 종류 판단
		switch (Event.type)
		{	//동작
			case Event::Closed:
			this->Window->close();
			break; //case 마지막에 반복실행 닫기

			case Event::KeyPressed:	//아무키 입력
			if (Event.key.code == Keyboard::Escape) // esc 입력하면, 키 눌림 이벤트
				this->Window->close();		// 윈도우창 닫기
			break;

		}
	}
}
void Game::Update(){
	//if(참)일때 실행 if(!false)실행
	this->EventHandler();
	if(!this->GameOverState)
	{
	//반복작업 포함하기
	
	this->UpdatePlayer();
	this->UpdateEnemy();
	this->CollisionCheck();
	this->UpdatePointText();
	}
}


//render
void Game::Render()
{
	//clear
	//Window.clear(Color::Cyan); //화면을 흰색으로 칠함, 
	//다양한 색을 원하는경우 rgb(색)a(투명도) 매개변수로 구현가능, 8비트(0~255)*3 = 24bit
	// //clear(Color(r,g,b,a)) a=0(투명)~255(불투명) 
	this->Window->clear(Color(50, 50, 50, 255));
	
	//draw player
	this->Window->draw(this->Player);
	
	//draw Enemy
	for (int i = 0; i < EnemyArray.size(); i++) {
		this->Window->draw(this->EnemyArray[i]);
	}
	//draw text
	this->Window->draw(this->PointText);
	this->Window->draw(this->GameOverText);

	//display, 마지막에
	this->Window->display(); //클리어에서 지정한 색을 표시해줌
}

//shut down
//소멸자
Game::~Game()
{
	this->DeleteWiondow();

}
void Game::DeleteWiondow()
{	// 윈도우 메모리에서 제거
	delete this->Window;
}

//element
//플레이어 위치 기능 정의
void Game::InitPlayer()
{	//플레이어 정보단계
	this->Player.setRadius(20.0f); // radius(반지름)(float형 0.f)
	this->Player.setFillColor(Color(50, 255, 255, 100));
	this->Player.setPosition(625,325);//윈도우내 플레이어 포인트 좌표값
	float(this->Window->getSize().x / 2) - 20.0f; //좌표기준은 왼쪽위부터 시작
	float(this->Window->getSize().y / 2) - 20.0f;

}
//플레이어 이동 기능 정의
void Game::UpdatePlayer()
{	//이벤트 없이 키입력,	반복실행
	//is(물어보기)keypressed(키가눌렀는지)Keyboard::Left(Left방향키가) 참인지
	//else if(지정한 방향만) if(모든방향)
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		this->Player.move(-5.0f, 0.0f); //플레이어 이동값 (x축,y축) -좌,+우
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		this->Player.move(5.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		this->Player.move(0.0f, -5.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		this->Player.move(0.0f, 5.0f);
	}
	//위치값 업데이트
}

//Enemy
//적 이동기능 정의
void Game::InitEnemy()
{	//적 정보단계
	this->Enemy.setSize(Vector2f(60.0f, 60.0f));
	this->Enemy.setFillColor(Color::Green);
	this->Enemy.setPosition(100, 100);
}

//
void Game::InitSpawn() {
	this->EnemyMax = 40;
	this->IntervalMax = 50.0f;
	this->IntervalStart = 0.0f;
}

//적 스폰기능 정의
//적 개체를 여러개 배열해야 할 경우
void  Game::SpawnEnemy(){
	//스폰된 적을 불규칙하게 움직이기,x값 불규칙하게 하기,형변환,rand()%1280(창x값크기)
	this->Enemy.setPosition(static_cast<float>(rand() % 1280), 0.0f);
	//벡터타입 데이터 추가.푸쉬백(하나씩 제거하기)
	this->EnemyArray.push_back(this->Enemy);
}
// 적 이동정의
void Game::UpdateEnemy()
{
	//Enemy Maxium
	if (this->EnemyArray.size() <= this->EnemyMax) 
	{
		//Enemy Spawn IntervalMax
		this->SpawnEnemy();
		if (this->IntervalMax <= this->IntervalStart)
		{
			this->SpawnEnemy();
			this->IntervalStart = 0.0f;
		}
		else 
		{
			this->IntervalStart += 1.0f;
		}
	}
	//적이동
	//this->Enemy.move(0.0f, 1.0f);
	//시간차이 없이 적이동 반복
	for (int i = 0; i< this->EnemyArray.size(); i++)
	{	//적 이동속도 x,y값
		this->EnemyArray[i].move(0.0f, 4.0f);
	}

	for (int i = 0; i < this->EnemyArray.size(); i++) 
	{
		//윈도우 밖으로 벗어난 Enemy 삭제 
		if (this->EnemyArray[i].getPosition().y >= this->Window->getSize().y)
		{
			this->EnemyArray.erase(this->EnemyArray.begin()+i);
			// 삭제되는 Enemy 개수 > 점수
			point++;

		}
	}

}

//Collision Check,충돌
void Game::CollisionCheck()
{
	for (int i = 0; i < EnemyArray.size(); i++)
	{	//경계를 찾아줌, 교차
		if (this->Player.getGlobalBounds().intersects(this->EnemyArray[i].getGlobalBounds()))
		{
			//충돌 : TRUE
			//게임종료
			//창닫기
			//this->DeleteWiondow();
			//게임오버 출력
			this->GameOverState = true;
			this->PrintGameOverText();
			
		}

	}
}

//font
void Game::InitFont()
{
	if(this->Font.loadFromFile("Font/NanumGothic.ttf"))
	{
		cout << "load comprite"<<endl;
	}
	else {
		cout << "load fail" << endl;
	}
}

//text
void Game::InitPointText()
{
	this->PointText.setFont(this->Font);//폰트파일 불러오기
	this->PointText.setCharacterSize(50); //폰트크기
	this->PointText.setFillColor(Color::White);
	//this->PointText.setPosition(20,20);
	//우측하단에 스코어 표시
	this->PointText.setPosition(
		this->Window->getSize().x - 270, this->Window->getSize().y - 80);
}
//점수누적갱신
void Game::UpdatePointText() 
{
	stringstream pt;
	pt << "Socre : " << point;
	this->PointText.setString(pt.str());
}	

void Game::InitGameOverText() 
{
	this->GameOverText.setFont(this->Font);//폰트파일 불러오기
	this->GameOverText.setCharacterSize(100); //폰트크기
	this->GameOverText.setFillColor(Color::White);
	//this->PointText.setPosition(20,20);
	//우측하단에 스코어 표시
	this->GameOverText.setPosition(
		this->Window->getSize().x/2 -300, this->Window->getSize().y/2-100);// 2로 나누면 가운데 표시
	
}

void Game::PrintGameOverText()
{
	stringstream go;
	go << "Game Over";
	this->GameOverText.setString(go.str());
}