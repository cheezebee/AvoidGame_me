#include "Game.h"

//startup
//������
Game::Game() //Ŭ����game, ������ �ҷ����� 
{
	//������ �ʱ�ȭ �� ���� �Լ� ��������
	this->InitWindowPointer();
	this->InitWindow();

	//player�ʱ�ȭ
	this->InitPlayer();

	//enemy�ʱ�ȭ
	this->InitEnemy();
	this->InitSpawn();

	//point �ʱ�ȭ
	this->point = 0;

	//font �ʱ�ȭ
	this->InitFont();

	//text �ʱ�ȭ
	this->InitPointText();
	
	//game over text �ʱ�ȭ
	this->InitGameOverText();

	//bool GameOverState �ʱ�ȭ
	this->GameOverState = false;
}
void Game::InitWindowPointer()
{	// ������ ���� �ֱ�ȭ
	this->Window = nullptr;  
}
void Game::InitWindow()	//�������
{	//������ ��������, ���� ��� �𼭸����� 
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game Test", Style::Titlebar | Style::Close);	//��������
	//�����ϰ� �ݺ� ����,(60������)
	this->Window->setFramerateLimit(60);
	
}

//update
const bool Game::Running() const
{
	return this->Window->isOpen();	//winow.isOpen = window(������)->isOpen
									//isOpen�� �ҵ����ͷ� ���ϵ�...boolŸ������ ���
}
void Game::EventHandler()
{
	while (this->Window->pollEvent(Event)) //��½� 0�� ��� ���, �Է½� ������ �ٲ�� pollevent ���� event�� ����.
	{	//�̺�Ʈ ���� �Ǵ�
		switch (Event.type)
		{	//����
			case Event::Closed:
			this->Window->close();
			break; //case �������� �ݺ����� �ݱ�

			case Event::KeyPressed:	//�ƹ�Ű �Է�
			if (Event.key.code == Keyboard::Escape) // esc �Է��ϸ�, Ű ���� �̺�Ʈ
				this->Window->close();		// ������â �ݱ�
			break;

		}
	}
}
void Game::Update(){
	//if(��)�϶� ���� if(!false)����
	this->EventHandler();
	if(!this->GameOverState)
	{
	//�ݺ��۾� �����ϱ�
	
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
	//Window.clear(Color::Cyan); //ȭ���� ������� ĥ��, 
	//�پ��� ���� ���ϴ°�� rgb(��)a(����) �Ű������� ��������, 8��Ʈ(0~255)*3 = 24bit
	// //clear(Color(r,g,b,a)) a=0(����)~255(������) 
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

	//display, ��������
	this->Window->display(); //Ŭ����� ������ ���� ǥ������
}

//shut down
//�Ҹ���
Game::~Game()
{
	this->DeleteWiondow();

}
void Game::DeleteWiondow()
{	// ������ �޸𸮿��� ����
	delete this->Window;
}

//element
//�÷��̾� ��ġ ��� ����
void Game::InitPlayer()
{	//�÷��̾� �����ܰ�
	this->Player.setRadius(20.0f); // radius(������)(float�� 0.f)
	this->Player.setFillColor(Color(50, 255, 255, 100));
	this->Player.setPosition(625,325);//�����쳻 �÷��̾� ����Ʈ ��ǥ��
	float(this->Window->getSize().x / 2) - 20.0f; //��ǥ������ ���������� ����
	float(this->Window->getSize().y / 2) - 20.0f;

}
//�÷��̾� �̵� ��� ����
void Game::UpdatePlayer()
{	//�̺�Ʈ ���� Ű�Է�,	�ݺ�����
	//is(�����)keypressed(Ű����������)Keyboard::Left(Left����Ű��) ������
	//else if(������ ���⸸) if(������)
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		this->Player.move(-5.0f, 0.0f); //�÷��̾� �̵��� (x��,y��) -��,+��
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
	//��ġ�� ������Ʈ
}

//Enemy
//�� �̵���� ����
void Game::InitEnemy()
{	//�� �����ܰ�
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

//�� ������� ����
//�� ��ü�� ������ �迭�ؾ� �� ���
void  Game::SpawnEnemy(){
	//������ ���� �ұ�Ģ�ϰ� �����̱�,x�� �ұ�Ģ�ϰ� �ϱ�,����ȯ,rand()%1280(âx��ũ��)
	this->Enemy.setPosition(static_cast<float>(rand() % 1280), 0.0f);
	//����Ÿ�� ������ �߰�.Ǫ����(�ϳ��� �����ϱ�)
	this->EnemyArray.push_back(this->Enemy);
}
// �� �̵�����
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
	//���̵�
	//this->Enemy.move(0.0f, 1.0f);
	//�ð����� ���� ���̵� �ݺ�
	for (int i = 0; i< this->EnemyArray.size(); i++)
	{	//�� �̵��ӵ� x,y��
		this->EnemyArray[i].move(0.0f, 4.0f);
	}

	for (int i = 0; i < this->EnemyArray.size(); i++) 
	{
		//������ ������ ��� Enemy ���� 
		if (this->EnemyArray[i].getPosition().y >= this->Window->getSize().y)
		{
			this->EnemyArray.erase(this->EnemyArray.begin()+i);
			// �����Ǵ� Enemy ���� > ����
			point++;

		}
	}

}

//Collision Check,�浹
void Game::CollisionCheck()
{
	for (int i = 0; i < EnemyArray.size(); i++)
	{	//��踦 ã����, ����
		if (this->Player.getGlobalBounds().intersects(this->EnemyArray[i].getGlobalBounds()))
		{
			//�浹 : TRUE
			//��������
			//â�ݱ�
			//this->DeleteWiondow();
			//���ӿ��� ���
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
	this->PointText.setFont(this->Font);//��Ʈ���� �ҷ�����
	this->PointText.setCharacterSize(50); //��Ʈũ��
	this->PointText.setFillColor(Color::White);
	//this->PointText.setPosition(20,20);
	//�����ϴܿ� ���ھ� ǥ��
	this->PointText.setPosition(
		this->Window->getSize().x - 270, this->Window->getSize().y - 80);
}
//������������
void Game::UpdatePointText() 
{
	stringstream pt;
	pt << "Socre : " << point;
	this->PointText.setString(pt.str());
}	

void Game::InitGameOverText() 
{
	this->GameOverText.setFont(this->Font);//��Ʈ���� �ҷ�����
	this->GameOverText.setCharacterSize(100); //��Ʈũ��
	this->GameOverText.setFillColor(Color::White);
	//this->PointText.setPosition(20,20);
	//�����ϴܿ� ���ھ� ǥ��
	this->GameOverText.setPosition(
		this->Window->getSize().x/2 -300, this->Window->getSize().y/2-100);// 2�� ������ ��� ǥ��
	
}

void Game::PrintGameOverText()
{
	stringstream go;
	go << "Game Over";
	this->GameOverText.setString(go.str());
}