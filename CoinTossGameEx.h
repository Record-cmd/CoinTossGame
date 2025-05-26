#pragma once
#include "LibConsole.hpp"
#include "LibGameTool.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum class CoinType//enum class: 열거형 클래스 접근할떄 CoinType::CT_BACK등을 사용
{
	CT_BACK = 0, CT_FRONT, CT_NULL, CT_ERR
};	//CT_FRONT = 1, CT_FRONT= 2


class CoinTossGameEx
{
public:
	CoinTossGameEx(void) {}
	~CoinTossGameEx(void) {}

	void play(void);
private:
	int nTotalScore = 0;	//점수 변수
	int nTotalTry = 0;	//시행횟수변수
	int nTotalWin = 0;	//맞춘횟수
	int nMenuNum = 0;	//메뉴선택변수
	double dbWinRate = 0.0;	//승률변수
	int nBetting = 0;	//베팅 변수
	std::string strName;
	std::vector<char> vUserInput;

	void showLogo(void);	//로고출력
	CoinType inputCoin(void);	//코인입력
	CoinType randCoin(void);	//랜덤코인
	void WinRate(void);//승률출력
	void checkCoin(CoinType nInput, CoinType nRand);	//코인정답체크
	void GamePlay(void);	//동전게임 부분
	void InputName(void);	//게임시작시 이름을 입력받음
	int InputMenuNum(void);	//메뉴선택
	void InputFile(void);	//게임 통계 파일저장
	void ShowMenu(void);	//메뉴창
protected:

};

inline void CoinTossGameEx::play(void)
{
	vUserInput.clear();
	using namespace std;
	int MenuNum = 0;
	string str;
	showLogo();
	
	while (1)
	{
		ShowMenu();
		MenuNum = InputMenuNum();
		switch (MenuNum)
		{
		case 1: //게임시작
		{
			InputName();
			cout << "게임중 스페이스바를 누르면 게임을 종료합니다." << endl;
			GamePlay();
			break;
		}
		case 2:	//게임통계 출력
		{
			mglib::settextcol(mglib::WHITE);
			cout << "(1)전게임에서 선택한 번호 출력, (2)사용자별 전적 출력" << endl;
			cout << "보고싶은 통계번호를 선택하세요 : " << endl;
			MenuNum = InputMenuNum();
			int j = 1;
			switch (MenuNum)
			{
			case 1:
				for (auto i : vUserInput)
				{
					cout << j <<"번째 선택: " << i << ", "<< endl;
					j++;
				}
				cout << endl;
				break;
			case 2:
				ifstream file("게임통계.txt");
				while (1)
				{
					getline(file, str);
					cout << str << endl;
					if (str == "")	//파일에 더이상 문자가없으면
					{
						break;	//빠져나옴
					}
				}
			}

			break;
		}
		case 3://프로그램종료
		{
			exit(0);	//프로그램 종료
		}
		}
	}
}
	

inline void CoinTossGameEx::showLogo(void)
{
	using namespace std;
	using namespace mglib;
	settextcol(GREEN);
	cout << "======================================" << endl;
	cout << "[동전 던지기 게임]" << endl << "개발자 : 최진환" << endl;
	cout << "======================================" << endl;
}

inline CoinType CoinTossGameEx::inputCoin(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(GREEN);
	cout << "동전 앞면(F)이나 뒷면(B)을 선택하세요." << endl;	//문자열 출력(string)
	settextcol(WHITE);
	cout << "당신의 선택은? ";
	char cInput = _getche();
	settextcol(GREEN);
	if (cInput == 'F' || cInput == 'f')
	{
		vUserInput.push_back(cInput);
		cout << endl << "앞면을 선택했습니다." << endl;	//문자열(string)출력; <<: 스트림 cout에 출력하는 기호 cout(consol output) endl(end of line 엔터 키)
		return CoinType::CT_FRONT;
	}
	else if (cInput == 'B' || cInput == 'b')
	{
		vUserInput.push_back(cInput);
		cout << endl << "뒷면을 선택했습니다." << endl;
		return CoinType::CT_BACK;
	}
	else if (cInput == ' ')
	{
		cout << "현제 게임 통계를 저장하고 게임을 종료합니다." << endl;
		return CoinType::CT_NULL;
	}
	else
	{
		settextcol(RED);
		cout << endl << "잘못입력했습니다." << endl;
		return CoinType::CT_ERR;
	}
}

inline CoinType CoinTossGameEx::randCoin(void)
{
	using namespace std;
	using namespace mglib;
	settextcol(BLUE);
	cout << "아무키나 누르면 동전을 던집니다." << endl;
	_getch();	//글자 한 자(char)입력;
	int nRand = randrange(0, 2);	//(0,2-1)범위에서 정수 난수 발생
	nTotalTry++;
	CoinType nRandCoin = (CoinType)nRand;
	if (nRandCoin == CoinType::CT_BACK)
	{
		cout << "나온 동전은 뒷면입니다." << endl;
	}
	else cout << "나온 동전은 앞면입니다." << endl;
	return nRandCoin;
}

inline void CoinTossGameEx::WinRate(void)
{
		using namespace std;
		cout << "승률은" << nTotalWin / (double)nTotalTry * 100 << "%입니다." << endl;// 승률 출력
		cout << "총 시행 횟수: " << nTotalTry << endl;
		cout << "총 맞춘 횟수: " << nTotalWin << endl;
		cout << "베팅 량: " << nBetting << endl;
		dbWinRate = nTotalWin / (double)nTotalTry * 100;
}

inline void CoinTossGameEx::checkCoin(CoinType nInput, CoinType nRand)
{
	using namespace mglib;
		using namespace std;

		if (nInput == nRand)
		{
			settextcol(RED);
			cout << "잘 했습니다. 동전을 맞추었습니다." << endl;
			nTotalScore++;
			nTotalWin++;	//맞춘횟수 추가
			nBetting++;
		}
		else //COinType이 다름
		{
			settextcol(BLUE);
			cout << endl << "아쉽네요. 동전 선택이 틀렸습니다." << endl;
			nTotalScore--;
			nBetting--;
		}
		settextcol(YELLOW);
		cout << "현재 스코어는 " << nTotalScore << "입니다." << endl << endl;
	
}

inline void CoinTossGameEx::GamePlay(void)
{
	using namespace std;
	mglib::randseed();
	mglib::settextcol(mglib::BLUE);
	cout << "얼마나 베팅하시겠습니까? : " << endl;
	cin >> nBetting;
	mglib::settextcol(mglib::RED);
	cout << nBetting << "만큼 베팅했습니다." << endl;
	mglib::settextcol(mglib::BLUE);
	cout << "초기 득점을 랜덤으로 설정합니다." << endl;

	nTotalScore = mglib::randrange(0, 10);
	mglib::settextcol(mglib::RED);
	cout << "초기득점은 " << nTotalScore << "점 입니다." << endl;
	mglib::settextcol(mglib::WHITE);
	while (1)
	{
		CoinType cInput = inputCoin();
		if (cInput == CoinType::CT_ERR)	//잘못된 문자 입력시 다시 입력받음
		{
			continue;
		}
		if (cInput == CoinType::CT_NULL)	//스페이스바 누를시 빠져나감
		{
			InputFile();
			break;	//빠져나감
		}
		CoinType nRand = randCoin();
		checkCoin(cInput, nRand);
		WinRate();
		

	}
}

inline void CoinTossGameEx::InputName(void)
{
	using namespace std;
	cout << "이름을 입력하세요 : " << endl;
	cin >> strName;
}

inline int CoinTossGameEx::InputMenuNum(void)
{
	using namespace std;
	cin >> nMenuNum;
	return nMenuNum;
}

inline void CoinTossGameEx::InputFile(void)
{
	using namespace std;
	ofstream file("게임통계.txt", ios::app);
	file << "=======================================" << endl;
	file << "이름 : " << strName << endl;
	file << "시행 횟수 : " << nTotalTry << "문제" << endl;
	file << "맞춘 횟수 : " << nTotalWin << "번" << endl;
	file << "점수 : " << nTotalScore << std::endl;
	file << "승률 : " << dbWinRate << "%" << endl;
	file << "최종베팅 : " << nBetting << endl;
}

inline void CoinTossGameEx::ShowMenu(void)
{
	using namespace std;
	mglib::settextcol(mglib::WHITE);
	cout << "(1)게임시작, (2)게임통계, (3)게임종료" << endl;
	cout << "메뉴를 선택하세요 : " << endl;
}
