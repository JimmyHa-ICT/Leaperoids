#include "GSGameOver.h"
#include "Util.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSGameOver::GSGameOver()
{

}


GSGameOver::~GSGameOver()
{
}



void GSGameOver::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_purple2");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 650);
	button->SetSize(275, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("kenvector_future");
	auto m_Text = std::make_shared< Text>(shader, font, "GAME OVER", TEXT_COLOR::CYAN, 2);
	m_Text->Set2DPosition(Vector2(screenWidth / 2 - 160, 150));
	m_textList.push_back(m_Text);

	auto m_Text2 = std::make_shared< Text>(shader, font, "YOUR SCORE", TEXT_COLOR::WHILE, 1.5);
	m_Text2->Set2DPosition(Vector2(screenWidth / 2 - 140, screenHeight / 2 - 100));
	m_textList.push_back(m_Text2);

	//text score
	std::string score = std::to_string(Util::GetFinalScore());
	auto m_scoreText = std::make_shared<Text>(shader, font, score, TEXT_COLOR::RED, 3);
	m_scoreText->Set2DPosition(Vector2(screenWidth / 2 - score.length() * 25, screenHeight / 2));
	m_textList.push_back(m_scoreText);

	//highscore text
	auto m_Text3 = std::make_shared< Text>(shader, font, "HIGH SCORE", TEXT_COLOR::WHILE, 1.2);
	m_Text3->Set2DPosition(Vector2(screenWidth / 2 - 105, screenHeight / 2 + 100));
	m_textList.push_back(m_Text3);

	std::string highScore = std::to_string(Util::GetHighScore());
	auto m_highScoreText = std::make_shared<Text>(shader, font, highScore, TEXT_COLOR::BLUE, 1.5);
	m_highScoreText->Set2DPosition(Vector2(screenWidth / 2 - highScore.length() * 15, screenHeight / 2 + 140));
	m_textList.push_back(m_highScoreText);
}

void GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{

}

void GSGameOver::Resume()
{

}


void GSGameOver::HandleEvents()
{

}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
	for (auto t : m_textList)
	{
		t->Draw();
	}
}
