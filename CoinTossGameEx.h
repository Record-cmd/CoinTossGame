#pragma once
#include "LibConsole.hpp"
#include "LibGameTool.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum class CoinType//enum class: ������ Ŭ���� �����ҋ� CoinType::CT_BACK���� ���
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
	int nTotalScore = 0;	//���� ����
	int nTotalTry = 0;	//����Ƚ������
	int nTotalWin = 0;	//����Ƚ��
	int nMenuNum = 0;	//�޴����ú���
	double dbWinRate = 0.0;	//�·�����
	int nBetting = 0;	//���� ����
	std::string strName;
	std::vector<char> vUserInput;

	void showLogo(void);	//�ΰ����
	CoinType inputCoin(void);	//�����Է�
	CoinType randCoin(void);	//��������
	void WinRate(void);//�·����
	void checkCoin(CoinType nInput, CoinType nRand);	//��������üũ
	void GamePlay(void);	//�������� �κ�
	void InputName(void);	//���ӽ��۽� �̸��� �Է¹���
	int InputMenuNum(void);	//�޴�����
	void InputFile(void);	//���� ��� ��������
	void ShowMenu(void);	//�޴�â
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
		case 1: //���ӽ���
		{
			InputName();
			cout << "������ �����̽��ٸ� ������ ������ �����մϴ�." << endl;
			GamePlay();
			break;
		}
		case 2:	//������� ���
		{
			mglib::settextcol(mglib::WHITE);
			cout << "(1)�����ӿ��� ������ ��ȣ ���, (2)����ں� ���� ���" << endl;
			cout << "������� ����ȣ�� �����ϼ��� : " << endl;
			MenuNum = InputMenuNum();
			int j = 1;
			switch (MenuNum)
			{
			case 1:
				for (auto i : vUserInput)
				{
					cout << j <<"��° ����: " << i << ", "<< endl;
					j++;
				}
				cout << endl;
				break;
			case 2:
				ifstream file("�������.txt");
				while (1)
				{
					getline(file, str);
					cout << str << endl;
					if (str == "")	//���Ͽ� ���̻� ���ڰ�������
					{
						break;	//��������
					}
				}
			}

			break;
		}
		case 3://���α׷�����
		{
			exit(0);	//���α׷� ����
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
	cout << "[���� ������ ����]" << endl << "������ : ����ȯ" << endl;
	cout << "======================================" << endl;
}

inline CoinType CoinTossGameEx::inputCoin(void)
{
	using namespace mglib;
	using namespace std;
	settextcol(GREEN);
	cout << "���� �ո�(F)�̳� �޸�(B)�� �����ϼ���." << endl;	//���ڿ� ���(string)
	settextcol(WHITE);
	cout << "����� ������? ";
	char cInput = _getche();
	settextcol(GREEN);
	if (cInput == 'F' || cInput == 'f')
	{
		vUserInput.push_back(cInput);
		cout << endl << "�ո��� �����߽��ϴ�." << endl;	//���ڿ�(string)���; <<: ��Ʈ�� cout�� ����ϴ� ��ȣ cout(consol output) endl(end of line ���� Ű)
		return CoinType::CT_FRONT;
	}
	else if (cInput == 'B' || cInput == 'b')
	{
		vUserInput.push_back(cInput);
		cout << endl << "�޸��� �����߽��ϴ�." << endl;
		return CoinType::CT_BACK;
	}
	else if (cInput == ' ')
	{
		cout << "���� ���� ��踦 �����ϰ� ������ �����մϴ�." << endl;
		return CoinType::CT_NULL;
	}
	else
	{
		settextcol(RED);
		cout << endl << "�߸��Է��߽��ϴ�." << endl;
		return CoinType::CT_ERR;
	}
}

inline CoinType CoinTossGameEx::randCoin(void)
{
	using namespace std;
	using namespace mglib;
	settextcol(BLUE);
	cout << "�ƹ�Ű�� ������ ������ �����ϴ�." << endl;
	_getch();	//���� �� ��(char)�Է�;
	int nRand = randrange(0, 2);	//(0,2-1)�������� ���� ���� �߻�
	nTotalTry++;
	CoinType nRandCoin = (CoinType)nRand;
	if (nRandCoin == CoinType::CT_BACK)
	{
		cout << "���� ������ �޸��Դϴ�." << endl;
	}
	else cout << "���� ������ �ո��Դϴ�." << endl;
	return nRandCoin;
}

inline void CoinTossGameEx::WinRate(void)
{
		using namespace std;
		cout << "�·���" << nTotalWin / (double)nTotalTry * 100 << "%�Դϴ�." << endl;// �·� ���
		cout << "�� ���� Ƚ��: " << nTotalTry << endl;
		cout << "�� ���� Ƚ��: " << nTotalWin << endl;
		cout << "���� ��: " << nBetting << endl;
		dbWinRate = nTotalWin / (double)nTotalTry * 100;
}

inline void CoinTossGameEx::checkCoin(CoinType nInput, CoinType nRand)
{
	using namespace mglib;
		using namespace std;

		if (nInput == nRand)
		{
			settextcol(RED);
			cout << "�� �߽��ϴ�. ������ ���߾����ϴ�." << endl;
			nTotalScore++;
			nTotalWin++;	//����Ƚ�� �߰�
			nBetting++;
		}
		else //COinType�� �ٸ�
		{
			settextcol(BLUE);
			cout << endl << "�ƽ��׿�. ���� ������ Ʋ�Ƚ��ϴ�." << endl;
			nTotalScore--;
			nBetting--;
		}
		settextcol(YELLOW);
		cout << "���� ���ھ�� " << nTotalScore << "�Դϴ�." << endl << endl;
	
}

inline void CoinTossGameEx::GamePlay(void)
{
	using namespace std;
	mglib::randseed();
	mglib::settextcol(mglib::BLUE);
	cout << "�󸶳� �����Ͻðڽ��ϱ�? : " << endl;
	cin >> nBetting;
	mglib::settextcol(mglib::RED);
	cout << nBetting << "��ŭ �����߽��ϴ�." << endl;
	mglib::settextcol(mglib::BLUE);
	cout << "�ʱ� ������ �������� �����մϴ�." << endl;

	nTotalScore = mglib::randrange(0, 10);
	mglib::settextcol(mglib::RED);
	cout << "�ʱ������ " << nTotalScore << "�� �Դϴ�." << endl;
	mglib::settextcol(mglib::WHITE);
	while (1)
	{
		CoinType cInput = inputCoin();
		if (cInput == CoinType::CT_ERR)	//�߸��� ���� �Է½� �ٽ� �Է¹���
		{
			continue;
		}
		if (cInput == CoinType::CT_NULL)	//�����̽��� ������ ��������
		{
			InputFile();
			break;	//��������
		}
		CoinType nRand = randCoin();
		checkCoin(cInput, nRand);
		WinRate();
		

	}
}

inline void CoinTossGameEx::InputName(void)
{
	using namespace std;
	cout << "�̸��� �Է��ϼ��� : " << endl;
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
	ofstream file("�������.txt", ios::app);
	file << "=======================================" << endl;
	file << "�̸� : " << strName << endl;
	file << "���� Ƚ�� : " << nTotalTry << "����" << endl;
	file << "���� Ƚ�� : " << nTotalWin << "��" << endl;
	file << "���� : " << nTotalScore << std::endl;
	file << "�·� : " << dbWinRate << "%" << endl;
	file << "�������� : " << nBetting << endl;
}

inline void CoinTossGameEx::ShowMenu(void)
{
	using namespace std;
	mglib::settextcol(mglib::WHITE);
	cout << "(1)���ӽ���, (2)�������, (3)��������" << endl;
	cout << "�޴��� �����ϼ��� : " << endl;
}
