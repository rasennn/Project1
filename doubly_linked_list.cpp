#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// スコアとユーザー名1人分のデータ
struct ScoreAndUsername {
	int score = 0;
	std::string username = "";
	
	// 1つ前、後のデータ
	ScoreAndUsername* prev = this;
	ScoreAndUsername* next = this;

	// 何も指定しないときのコンストラクタ
	ScoreAndUsername() : score(0), username(""), prev(this), next(this) {};
	// データの中身を指定するときのコンストラクタ
	ScoreAndUsername(int _score, std::string _username) : score(_score), username(_username), prev(this), next(this) {};
};

struct DoublyLinkedList {
	// リストの先頭、末尾を表す。この要素に中身のデータはない。
	ScoreAndUsername head;
	ScoreAndUsername tail;

	// データの連結の初期化
	DoublyLinkedList() {
		head.next = &tail;
		tail.prev = &head;
	}

	//リストの末尾に要素を追加する
	void InsertLast(ScoreAndUsername* dataPtr) {
		// 追加前における最後の要素。リストが空の時はheadを指す。
		ScoreAndUsername* lastPtr = tail.prev;

		// last, data, tailの順に繋ぎ変える
		lastPtr->next = dataPtr;
		dataPtr->prev = lastPtr;
		dataPtr->next = &tail;
		tail.prev = dataPtr;
	}

	// 要素を先頭から順に出力する
	void PrintAll() {
		// 先頭から順に走査するポインタ。中身のあるデータだけを見るので、headの次から始める
		ScoreAndUsername* currentPtr = head.next;

		while (currentPtr != &tail) {
			std::cout << currentPtr->score << " " << currentPtr->username << std::endl;
			currentPtr = currentPtr->next;
		}
	}
};

int main(){
	// ファイル入力ストリームの準備
	const std::string FILENAME = "Scores.txt";
	std::ifstream ifs;
	ifs.open(FILENAME);

	// 入力を格納する配列
	std::vector<int> scores;
	std::vector<std::string> usernames;

	// 1行ずつ入力を受け取る
	std::string line;
	while(std::getline(ifs, line)){
		// 空白で区切る
		std::string::size_type tabPos = line.find('\t');

		// 空白がなければ終了
		if (tabPos == std::string::npos) { break; }

		// 入力を受け取る一時的な変数
		// スコアをまず文字列として受け取る
		std::string scoreStr = line.substr(0, tabPos);
		// 文字列を数値に変換
		int score = std::stoi(scoreStr);
		//ユーザーネームを受け取る
		std::string username = line.substr(tabPos + 1);

		// vectorに格納
		scores.push_back(score);
		usernames.push_back(username);
	}

	// ScoreAndUsernameを格納する場所（双方向リストのアクセス先）
	std::vector<ScoreAndUsername> scoreDatas(scores.size());
	DoublyLinkedList scoreList;

	// 双方向リストの構成
	for (int i = 0; i < scores.size(); i++) {
		scoreDatas[i] = ScoreAndUsername(scores[i], usernames[i]);
		scoreList.InsertLast(&scoreDatas[i]);
	}

	scoreList.PrintAll();
	
	return 0;
}