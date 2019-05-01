#include <iostream>
#include <map>
#include <vector>
#include <llvm-c/IR/value.h>


class ASTNode {
private:
	int id;

public:
	static int idCnt;

	virtual ~ASTNode() = default;
	virtual llvm::Value * codeGen(CodeGenContext &context) {
		return 0;
	}
	virtual std::vector<ASTNode *> getChildren() = 0;

	ASTNode(){
		id = ++idCnt;
	}
};

class Program : public ASTNode {
	ProgramHead * programhead = 0;
	Routine * routine = 0;
}