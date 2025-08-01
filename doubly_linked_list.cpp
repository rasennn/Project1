#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// �X�R�A�ƃ��[�U�[��1�l���̃f�[�^
struct ScoreAndUsername {
	int score = 0;
	std::string username = "";
	
	// 1�O�A��̃f�[�^
	ScoreAndUsername* prev = this;
	ScoreAndUsername* next = this;

	// �����w�肵�Ȃ��Ƃ��̃R���X�g���N�^
	ScoreAndUsername() : score(0), username(""), prev(this), next(this) {};
	// �f�[�^�̒��g���w�肷��Ƃ��̃R���X�g���N�^
	ScoreAndUsername(int _score, std::string _username) : score(_score), username(_username), prev(this), next(this) {};
};

struct DoublyLinkedList {
	// ���X�g�̐擪�A������\���B���̗v�f�ɒ��g�̃f�[�^�͂Ȃ��B
	ScoreAndUsername head;
	ScoreAndUsername tail;

	// �f�[�^�̘A���̏�����
	DoublyLinkedList() {
		head.next = &tail;
		tail.prev = &head;
	}

	//���X�g�̖����ɗv�f��ǉ�����
	void InsertLast(ScoreAndUsername* dataPtr) {
		// �ǉ��O�ɂ�����Ō�̗v�f�B���X�g����̎���head���w���B
		ScoreAndUsername* lastPtr = tail.prev;

		// last, data, tail�̏��Ɍq���ς���
		lastPtr->next = dataPtr;
		dataPtr->prev = lastPtr;
		dataPtr->next = &tail;
		tail.prev = dataPtr;
	}

	// �v�f��擪���珇�ɏo�͂���
	void PrintAll() {
		// �擪���珇�ɑ�������|�C���^�B���g�̂���f�[�^����������̂ŁAhead�̎�����n�߂�
		ScoreAndUsername* currentPtr = head.next;

		while (currentPtr != &tail) {
			std::cout << currentPtr->score << " " << currentPtr->username << std::endl;
			currentPtr = currentPtr->next;
		}
	}
};

int main(){
	// �t�@�C�����̓X�g���[���̏���
	const std::string FILENAME = "Scores.txt";
	std::ifstream ifs;
	ifs.open(FILENAME);

	// ���͂��i�[����z��
	std::vector<int> scores;
	std::vector<std::string> usernames;

	// 1�s�����͂��󂯎��
	std::string line;
	while(std::getline(ifs, line)){
		// �󔒂ŋ�؂�
		std::string::size_type tabPos = line.find('\t');

		// �󔒂��Ȃ���ΏI��
		if (tabPos == std::string::npos) { break; }

		// ���͂��󂯎��ꎞ�I�ȕϐ�
		// �X�R�A���܂�������Ƃ��Ď󂯎��
		std::string scoreStr = line.substr(0, tabPos);
		// ������𐔒l�ɕϊ�
		int score = std::stoi(scoreStr);
		//���[�U�[�l�[�����󂯎��
		std::string username = line.substr(tabPos + 1);

		// vector�Ɋi�[
		scores.push_back(score);
		usernames.push_back(username);
	}

	// ScoreAndUsername���i�[����ꏊ�i�o�������X�g�̃A�N�Z�X��j
	std::vector<ScoreAndUsername> scoreDatas(scores.size());
	DoublyLinkedList scoreList;

	// �o�������X�g�̍\��
	for (int i = 0; i < scores.size(); i++) {
		scoreDatas[i] = ScoreAndUsername(scores[i], usernames[i]);
		scoreList.InsertLast(&scoreDatas[i]);
	}

	scoreList.PrintAll();
	
	return 0;
}