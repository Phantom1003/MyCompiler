#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "utils.hpp"

#ifndef AST_H
#define AST_H

class ASTNode {
public:
	int id;
	static int idCnt;
	ASTNode(){
		id = ++idCnt;
	}

	virtual ~ASTNode(){};
	// virtual llvm::Value * codeGen(CodeGenContext &context) {
	// 	return 0;
	// }
	virtual std::vector<ASTNode *> getChildren() {return std::vector<ASTNode *>();};
	virtual std::string getName() { return "";};

};

int ASTNode::idCnt = 0;

class Program;
class ProgramHead;
class Routine;
class SubRoutine;
class RoutineHead;
class LabelPart;
class ConstPart;
class ConstExprList;
class ConstValue;
class TypePart;
class TypeDeclList;
class TypeDefinition;
class TypeDecl;
class SimpleTypeDecl;
class ArrayTypeDecl;
class RecordTypeDecl;
class FieldDeclList;
class FieldDecl;
class NameList;
class VarPart;
class VarDeclList;
class VarDecl;
class RoutinePart;
class FunctionDecl;
class FunctionHead;
class ProcedureDecl;
class ProcedureHead;
class Parameters;
class ParaDeclList;
class ParaTypeList;
class VarParaList;
class ValParaList;
class RoutineBody;
class CompoundStmt;
class StmtList;
class Stmt;
class NonLabelStmt;
class AssignStmt;
class ProcStmt;
class IfStmt;
class ElseClause;
class RepeatStmt;
class WhileStmt;
class ForStmt;
class Direction;
class CaseStmt;
class CaseExprList;
class CaseExpr;
class GotoStmt;
class ExpressionList;
class Expression;
class Expr;
class Term;
class Factor;
class ArgsList;


class Program : public ASTNode {
public:
	ProgramHead * programHead;
	Routine * routine;

	explicit Program(ProgramHead *programHead, Routine *routine) : programHead(programHead), routine(routine) {}
	
	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(programHead);
		ch.emplace_back(routine);
		return ch;
	}

	~Program() {
		delete programHead;
		delete routine;
	}
};

class ProgramHead : public ASTNode {
public:
	std::string name;

	explicit ProgramHead(std::string name) : name(std::move(name)) {}

	std::vector<ASTNode *> getChildren() {
		return std::vector<ASTNode *> ();
	}

	std::string getName(){
		return name;
	}
};

class Routine : public ASTNode {
public:
	RoutineHead * routineHead;
	RoutineBody * routineBody;

	explicit Routine(RoutineHead *routineHead, RoutineBody * routineBody) : routineHead(routineHead), routineBody(routineBody) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(routineHead);
		ch.emplace_back(routineBody);
		return ch;
	}
	~Routine() {
		delete routineHead;
		delete routineBody;
	}
};

class SubRoutine : public ASTNode {
public:
	RoutineHead * routineHead;
	RoutineBody * routineBody;

	explicit SubRoutine(RoutineHead *routineHead, RoutineBody * routineBody) : routineHead(routineHead), routineBody(routineBody) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(routineHead);
		ch.emplace_back(routineBody);
		return ch;
	}
	~SubRoutine() {
		delete routineHead;
		delete routineBody;
	}
};

class RoutineHead : public ASTNode {
public:
	LabelPart * labelPart;
	ConstPart * constPart;
	TypePart * typePart;
	VarPart * varPart;
	RoutinePart * routinePart;

	explicit RoutineHead(LabelPart *labelPart, ConstPart *constPart, TypePart *typePart, VarPart *varPart, RoutinePart *routinePart) : labelPart(labelPart), constPart(constPart), typePart(typePart), varPart(varPart), routinePart(routinePart) {}

	std::vector<ASTNode *> getChildren() {
        std::vector<ASTNode *> ch = std::vector<ASTNode *>();
        ch.emplace_back(labelPart);
        ch.emplace_back(constPart);
        ch.emplace_back(typePart);
        ch.emplace_back(varPart);
        ch.emplace_back(routinePart);
        return ch;
    }
    ~RoutineHead() {
    	delete labelPart;
    	delete constPart;
    	delete typePart;
    	delete varPart;
    	delete routinePart;
    }
};

class LabelPart : public ASTNode {
public:

	std::vector<ASTNode *> getChildren() {
		return std::vector<ASTNode *>();
	}
};

class ConstPart : public ASTNode {
public:
	ConstExprList * constExprList;

	explicit ConstPart(ConstExprList *constExprList) : constExprList(constExprList) {}
	explicit ConstPart() {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(constExprList)
			ch.emplace_back(constExprList);
		return ch;
	}
};

class ConstExprList : public ASTNode {
public:
	std::string name;
	ConstExprList * preList;
	ConstValue * constValue;

	explicit ConstExprList(std::string name, ConstExprList *preList, ConstValue * constValue) : name(std::move(name)), preList(preList), constValue(constValue) {}

	explicit ConstExprList(std::string name, ConstValue * constValue) : name(std::move(name)), constValue(constValue) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(constValue);
		return ch;
	}
};

class ConstValue : public ASTNode {
public:
	int token;
	std::string value;

	explicit ConstValue(int token, std::string value) : token(token), value(std::move(value)) {}

	std::vector<ASTNode *> getChildren() {
		return std::vector<ASTNode *>();
	}

	ConstValue * neg() {
		if(token == 286) {
			return new ConstValue(286, i2s(-s2i(value)));
		}
		else if(token == 287) {
			return new ConstValue(287, d2s(-s2d(value)));
		}
		else {
			return new ConstValue(token, value);
		}
	}
};

class TypePart : public ASTNode {
public:
	TypeDeclList * typeDeclList;

	explicit TypePart(TypeDeclList * typeDeclList) : typeDeclList(typeDeclList) {}

	TypePart() {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(typeDeclList);
		return ch;
	}
};

class TypeDeclList : public ASTNode {
public:
	TypeDeclList * preList;
	TypeDefinition * typeDefinition;

	explicit TypeDeclList(TypeDeclList * preList, TypeDefinition * typeDefinition) : preList(preList), typeDefinition(typeDefinition) {}
	
	explicit TypeDeclList(TypeDefinition * typeDefinition) : typeDefinition(typeDefinition) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(typeDefinition);
		return ch;
	}
};

class TypeDefinition : public ASTNode {
public:
	std::string name;
	TypeDecl * typeDecl;

	explicit TypeDefinition(std::string name, TypeDecl * typeDecl) : name(std::move(name)), typeDecl(typeDecl) {}
	
	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(typeDecl);
		return ch;
	}

	std::string getName() {
		return std::move(name);
	}
};

class TypeDecl : public ASTNode {
public:
	SimpleTypeDecl * simpleTypeDecl{};
	ArrayTypeDecl * arrayTypeDecl{};
	RecordTypeDecl * recordTypeDecl{};

	explicit TypeDecl(SimpleTypeDecl * simpleTypeDecl) : simpleTypeDecl(simpleTypeDecl) {}

	explicit TypeDecl(ArrayTypeDecl * arrayTypeDecl) : arrayTypeDecl(arrayTypeDecl) {}
	
	explicit TypeDecl(RecordTypeDecl * recordTypeDecl) : recordTypeDecl(recordTypeDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(simpleTypeDecl)
			ch.emplace_back(simpleTypeDecl);
		if(arrayTypeDecl)
			ch.emplace_back(arrayTypeDecl);
		if(recordTypeDecl)
			ch.emplace_back(recordTypeDecl);
		return ch;
	}

	~TypeDecl() {
		delete simpleTypeDecl;
		delete arrayTypeDecl;
		delete recordTypeDecl;
	}
};

class SimpleTypeDecl : public ASTNode {
public:
	std::string sysType;
	std::string name;

	NameList * nameList;
	ConstValue * lowerValue, * upperValue;
	std::string lowerName, upperName;

	explicit SimpleTypeDecl(int token, std::string value) {
		if(token == 284)
			sysType = std::move(value);
		if(token == 258)
			name = std::move(value);
	}

	explicit SimpleTypeDecl(NameList * nameList) : nameList(nameList) {}

	explicit SimpleTypeDecl(ConstValue * lowerValue, ConstValue * upperValue) : lowerValue(lowerValue), upperValue(upperValue) {}

	explicit SimpleTypeDecl(std::string lowerName, std::string upperName) : lowerName(std::move(lowerName)), upperName(std::move(upperName)) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(nameList)
			ch.emplace_back(nameList);
		if(lowerValue && upperValue){
			ch.emplace_back(lowerValue);
			ch.emplace_back(upperValue);
		}
		return ch;
	}
	~SimpleTypeDecl() {
		delete nameList;
		delete lowerValue;
		delete upperValue;
	}
};

class ArrayTypeDecl : public ASTNode {
public:
	SimpleTypeDecl * simpleTypeDecl;
	TypeDecl * typeDecl;

	explicit ArrayTypeDecl(SimpleTypeDecl * simpleTypeDecl, TypeDecl * typeDecl) : simpleTypeDecl(simpleTypeDecl), typeDecl(typeDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(simpleTypeDecl);
		ch.emplace_back(typeDecl);
		return ch;
	}

	~ArrayTypeDecl() {
		delete simpleTypeDecl;
		delete typeDecl;
	}
};

class RecordTypeDecl : public ASTNode {
public:
	FieldDeclList * fieldDeclList;

	explicit RecordTypeDecl(FieldDeclList * fieldDeclList) : fieldDeclList(fieldDeclList) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(fieldDeclList);
		return ch;
	}

	~RecordTypeDecl() {
		delete fieldDeclList;
	}
};

class FieldDeclList : public ASTNode {
public:
	FieldDeclList * preList;
	FieldDecl * fieldDecl;

	explicit FieldDeclList(FieldDeclList * preList, FieldDecl * fieldDecl) : preList(preList), fieldDecl(fieldDecl) {}

	explicit FieldDeclList(FieldDecl * fieldDecl) : fieldDecl(fieldDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(fieldDecl);
		return ch;
	}

	~FieldDeclList() {
		delete preList;
		delete fieldDecl;
	}
};

class FieldDecl : public ASTNode {
public:
	NameList * nameList;
	TypeDecl * typeDecl;

	explicit FieldDecl(NameList * nameList, TypeDecl * typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(nameList);
		ch.emplace_back(typeDecl);
		return ch;
	}

	~FieldDecl() {
		delete nameList;
		delete typeDecl;
	}
};

class NameList : public ASTNode {
public:
	NameList * preList;
	std::string name;

	explicit NameList(std::string name, NameList * preList) : name(std::move(name)), preList(preList) {}

	explicit NameList(std::string name) : name(std::move(name)) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(preList);
		return ch;
	}

	std::string getName() {
		return std::move(name);
	}

	~NameList() {
		delete preList;
	}
};

class VarPart : public ASTNode {
public:
	VarDeclList * varDeclList;

	explicit VarPart(VarDeclList * varDeclList) : varDeclList(varDeclList) {}

	VarPart(){}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(varDeclList);
		return ch;
	}

	~VarPart() {
		delete varDeclList;
	}
};

class VarDeclList : public ASTNode {
public:
	VarDeclList * preList;
	VarDecl * varDecl;

	explicit VarDeclList(VarDeclList * preList, VarDecl * varDecl) : preList(preList), varDecl(varDecl) {}

	explicit VarDeclList(VarDecl * varDecl) : varDecl(varDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(varDecl);
		return ch;
	}

	~VarDeclList() {
		delete preList;
		delete varDecl;
	}
};

class VarDecl : public ASTNode {
public:
	NameList * nameList;
	TypeDecl * typeDecl;

	explicit VarDecl(NameList * nameList, TypeDecl * typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(nameList);
		ch.emplace_back(typeDecl);
		return ch;
	}

	~VarDecl() {
		delete nameList;
		delete typeDecl;
	}
};

class RoutinePart : public ASTNode {
public:
	RoutinePart * prePart;
	FunctionDecl * functionDecl;
	ProcedureDecl * procedureDecl;

	explicit RoutinePart(RoutinePart * prePart, FunctionDecl * functionDecl) : prePart(prePart), functionDecl(functionDecl) {}

	explicit RoutinePart(RoutinePart * prePart, ProcedureDecl * procedureDecl) : prePart(prePart), procedureDecl(procedureDecl) {}

	explicit RoutinePart(FunctionDecl * functionDecl) : functionDecl(functionDecl) {}

	explicit RoutinePart(ProcedureDecl * procedureDecl) : procedureDecl(procedureDecl) {}

	RoutinePart() {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(prePart)
			ch.emplace_back(prePart);
		if(functionDecl)
			ch.emplace_back(functionDecl);
		if(procedureDecl)
			ch.emplace_back(procedureDecl);
		return ch;
	}

	~RoutinePart() {
		delete prePart;
		delete functionDecl;
		delete procedureDecl;
	}
};

class FunctionDecl : public ASTNode {
public:
	FunctionHead * functionHead;
	SubRoutine * subRoutine;

	explicit FunctionDecl(FunctionHead * functionHead, SubRoutine * subRoutine) : functionHead(functionHead), subRoutine(subRoutine) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(functionHead);
		ch.emplace_back(subRoutine);
		return ch;
	}

	~FunctionDecl() {
		delete functionHead;
		delete subRoutine;
	}
};

class FunctionHead : public ASTNode {
public:
	std::string name;
	Parameters * parameters;
	SimpleTypeDecl * simpleTypeDecl;

	explicit FunctionHead(std::string name, Parameters * parameters, SimpleTypeDecl * simpleTypeDecl) : name(name), parameters(parameters), simpleTypeDecl(simpleTypeDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(parameters);
		ch.emplace_back(simpleTypeDecl);
		return ch;
	}

	std::string getName() {
		return std::move(name);
	}

	~FunctionHead() {
		delete parameters;
		delete simpleTypeDecl;
	}
};

class ProcedureDecl : public ASTNode {
public:
	ProcedureHead * procedureHead;
	SubRoutine * subRoutine;

	explicit ProcedureDecl(ProcedureHead * procedureHead, SubRoutine * subRoutine) : procedureHead(procedureHead), subRoutine(subRoutine) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(procedureHead);
		ch.emplace_back(subRoutine);
		return ch;
	}

	~ProcedureDecl() {
		delete procedureHead;
		delete subRoutine;
	}
};

class ProcedureHead : public ASTNode {
public:
	Parameters * parameters;
	std::string name;

	explicit ProcedureHead(std::string name, Parameters * parameters) : name(std::move(name)), parameters(parameters) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(parameters);
		return ch;
	}

	~ProcedureHead() {
		delete parameters;
	}
};

class Parameters : public ASTNode {
public:
	ParaDeclList * paraDeclList;

	explicit Parameters(ParaDeclList * paraDeclList) : paraDeclList(paraDeclList) {}
	explicit Parameters() {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(paraDeclList)
			ch.emplace_back(paraDeclList);
		return ch;
	}

	~Parameters() {
		delete paraDeclList;
	}
};

class ParaDeclList : public ASTNode {
public:
	ParaDeclList * preList;
	ParaTypeList * paraTypeList;

	explicit ParaDeclList(ParaDeclList * preList, ParaTypeList * paraTypeList) : preList(preList), paraTypeList(paraTypeList) {}

	explicit ParaDeclList(ParaTypeList * paraTypeList) : paraTypeList(paraTypeList) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(paraTypeList);
		return ch;
	}
};

class ParaTypeList : public ASTNode {
public:
	VarParaList * varParaList;
	ValParaList * valParaList;
	SimpleTypeDecl * simpleTypeDecl;

	explicit ParaTypeList(VarParaList * varParaList, SimpleTypeDecl * simpleTypeDecl) : varParaList(varParaList), simpleTypeDecl(simpleTypeDecl) {}

	explicit ParaTypeList(ValParaList * valParaList, SimpleTypeDecl * simpleTypeDecl) : valParaList(valParaList), simpleTypeDecl(simpleTypeDecl) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(varParaList)
			ch.emplace_back(varParaList);
		if(valParaList)
			ch.emplace_back(valParaList);
		ch.emplace_back(simpleTypeDecl);
		return ch;
	}

	~ParaTypeList() {
		delete varParaList;
		delete valParaList;
	}
};

class VarParaList : public ASTNode {
public:
	NameList * nameList;

	explicit VarParaList(NameList * nameList) : nameList(nameList) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(nameList);
		return ch;
	}

	~VarParaList() {
		delete nameList;
	}
};

class ValParaList : public ASTNode {
public:
	NameList * nameList;

	explicit ValParaList(NameList * nameList) : nameList(nameList) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(nameList);
		return ch;
	}

	~ValParaList() {
		delete nameList;
	}
};

class RoutineBody : public ASTNode {
public:
	CompoundStmt * compoundStmt;

	explicit RoutineBody(CompoundStmt * compoundStmt) : compoundStmt(compoundStmt) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(compoundStmt);
		return ch;
	}

	~RoutineBody() {
		delete compoundStmt;
	}
};

class CompoundStmt : public ASTNode {
public:
	StmtList * stmtList;

	explicit CompoundStmt(StmtList * stmtList) : stmtList(stmtList) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(stmtList);
		return ch;
	}

	~CompoundStmt() {
		delete stmtList;
	}
};

class StmtList : public ASTNode {
public:
	StmtList * preList;
	Stmt * stmt;

	explicit StmtList(StmtList * preList, Stmt * stmt) : preList(preList), stmt(stmt) {}

	explicit StmtList() {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(stmt);
		return ch;
	}

	~StmtList() {
		delete preList;
		delete stmt;
	}
};

class Stmt : public ASTNode {
public:
	std::string label;
	NonLabelStmt * nonLabelStmt;

	explicit Stmt(std::string label, NonLabelStmt * nonLabelStmt) : label(std::move(label)), nonLabelStmt(nonLabelStmt) {}

	explicit Stmt(NonLabelStmt * nonLabelStmt) : nonLabelStmt(nonLabelStmt) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(nonLabelStmt);
		return ch;
	}

	~Stmt() {
		delete nonLabelStmt;
	}
};

class NonLabelStmt : public ASTNode {
public:
	AssignStmt * assignStmt;
	ProcStmt * procStmt;
	CompoundStmt * compoundStmt;
	IfStmt * ifStmt;
	RepeatStmt * repeatStmt;
	WhileStmt * whileStmt;
	ForStmt * forStmt;
	CaseStmt * caseStmt;
	GotoStmt * gotoStmt;

	explicit NonLabelStmt(AssignStmt * assignStmt) : assignStmt(assignStmt) {}

	explicit NonLabelStmt(ProcStmt * procStmt) : procStmt(procStmt) {}
	
	explicit NonLabelStmt(CompoundStmt * compoundStmt) : compoundStmt(compoundStmt) {}
	
	explicit NonLabelStmt(IfStmt * ifStmt) : ifStmt(ifStmt) {}
	
	explicit NonLabelStmt(RepeatStmt * repeatStmt) : repeatStmt(repeatStmt) {}
	
	explicit NonLabelStmt(WhileStmt * whileStmt) : whileStmt(whileStmt) {}
	
	explicit NonLabelStmt(ForStmt * forStmt) : forStmt(forStmt) {}
	
	explicit NonLabelStmt(CaseStmt * caseStmt) : caseStmt(caseStmt) {}
	
	explicit NonLabelStmt(GotoStmt * gotoStmt) : gotoStmt(gotoStmt) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(assignStmt)
			ch.emplace_back(assignStmt);
		if(procStmt)
			ch.emplace_back(procStmt);
		if(compoundStmt)
			ch.emplace_back(compoundStmt);
		if(ifStmt)
			ch.emplace_back(ifStmt);
		if(repeatStmt)
			ch.emplace_back(repeatStmt);
		if(whileStmt)
			ch.emplace_back(whileStmt);
		if(forStmt)
			ch.emplace_back(forStmt);
		if(caseStmt)
			ch.emplace_back(caseStmt);
		if(gotoStmt)
			ch.emplace_back(gotoStmt);
		return ch;
	}
	
	~NonLabelStmt() {
		delete assignStmt;
		delete procStmt;
		delete compoundStmt;
		delete ifStmt;
		delete repeatStmt;
		delete whileStmt;
		delete forStmt;
		delete caseStmt;
		delete gotoStmt;
	}
};

class AssignStmt : public ASTNode {
public:
	std::string name, attr;
	Expression * expression, * index;

	explicit AssignStmt(std::string name, Expression * expression) : name(std::move(name)), expression(expression) {}

	explicit AssignStmt(std::string name, Expression * index, Expression * expression) : name(std::move(name)), index(index), expression(expression) {}

	explicit AssignStmt(std::string name, std::string attr, Expression * expression) : name(std::move(name)), attr(std::move(attr)), expression(expression) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(index)
			ch.emplace_back(index);
		ch.emplace_back(expression);
		return ch;
	}

	~AssignStmt() {
		delete expression;
		delete index;
	}
};

class ProcStmt : public ASTNode {
public:
	std::string name, sysProc;
	ArgsList * argsList;
	ExpressionList * expressionList;
	Factor * factor;

	explicit ProcStmt(bool isSysProc, std::string val) {
		if(!isSysProc)
			name = std::move(val);
		else
			sysProc = std::move(val);
	}

	explicit ProcStmt(std::string name, ArgsList * argsList) : name(std::move(name)), argsList(argsList) {}

	explicit ProcStmt(std::string sysProc, ExpressionList * expressionList) : sysProc(std::move(sysProc)), expressionList(expressionList) {}

	explicit ProcStmt(Factor * factor) : factor(factor) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(argsList)
			ch.emplace_back(argsList);
		if(expressionList)
			ch.emplace_back(expressionList);
		if(factor)
			ch.emplace_back(factor);
		return ch;
	}

	~ProcStmt() {
		delete argsList;
		delete expressionList;
		delete factor;
	}
};

class IfStmt : public ASTNode {
public:
	Expression * expression;
	Stmt * stmt;
	ElseClause * elseClause;

	explicit IfStmt(Expression * expression, Stmt * stmt, ElseClause * elseClause) : expression(expression), stmt(stmt), elseClause(elseClause) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(expression);
		ch.emplace_back(stmt);
		ch.emplace_back(elseClause);
		return ch;
	}

	~IfStmt() {
		delete expression;
		delete stmt;
		delete elseClause;
	}
};

class ElseClause : public ASTNode {
public:
	Stmt * stmt;

	explicit ElseClause(Stmt * stmt) : stmt(stmt) {}

	ElseClause() {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(stmt);
		return ch;
	}

	~ElseClause() {
		delete stmt;
	}
};

class RepeatStmt : public ASTNode {
public:
	StmtList * stmtList;
	Expression * expression;

	explicit RepeatStmt(StmtList * stmtList, Expression * expression) : stmtList(stmtList), expression(expression) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(stmtList);
		ch.emplace_back(expression);
		return ch;
	}

	~RepeatStmt() {
		delete stmtList;
	}
};

class WhileStmt : public ASTNode {
public:
	Expression * expression;
	Stmt * stmt;

	explicit WhileStmt(Expression * expression, Stmt * stmt) : expression(expression), stmt(stmt) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(expression);
		ch.emplace_back(stmt);
		return ch;
	}

	~WhileStmt() {
		delete expression;
		delete stmt;
	}
};

class ForStmt : public ASTNode {
public:
	std::string name;
	Expression * expr1, * expr2;
	Direction * direction;
	Stmt * stmt;

	explicit ForStmt(std::string name, Expression * expr1, Direction * direction, Expression * expr2, Stmt * stmt) : name(std::move(name)), expr1(expr1), direction(direction), expr2(expr2), stmt(stmt) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(expr1);
		ch.emplace_back(direction);
		ch.emplace_back(expr2);
		ch.emplace_back(stmt);
		return ch;
	}

	~ForStmt() {
		delete expr1;
		delete expr2;
		delete direction;
		delete stmt;
	}
};

class Direction : public ASTNode {
public:
	std::string dir;

	explicit Direction(std::string dir) : dir(std::move(dir)) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		return ch;
	}
};

class CaseStmt : public ASTNode {
public:
	Expression * expression;
	CaseExprList * caseExprList;

	explicit CaseStmt(Expression * expression, CaseExprList * caseExprList) : expression(expression), caseExprList(caseExprList) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(expression);
		ch.emplace_back(caseExprList);
		return ch;
	}

	~CaseStmt() {
		delete expression;
		delete caseExprList;
	}
};

class CaseExprList : public ASTNode {
public:
	CaseExprList * preList;
	CaseExpr * caseExpr;

	explicit CaseExprList(CaseExprList * preList, CaseExpr * caseExpr) : preList(preList), caseExpr(caseExpr) {}

	explicit CaseExprList(CaseExpr * caseExpr) : caseExpr(caseExpr) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(caseExpr);
		return ch;
	}

	~CaseExprList() {
		delete preList;
		delete caseExpr;
	}
};

class CaseExpr : public ASTNode {
public:
	std::string name;
	ConstValue * constValue;
	Stmt * stmt;

	explicit CaseExpr(ConstValue * constValue, Stmt * stmt) : constValue(constValue), stmt(stmt) {}

	explicit CaseExpr(std::string name, Stmt * stmt) : name(std::move(name)), stmt(stmt) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(constValue)
			ch.emplace_back(constValue);
		ch.emplace_back(stmt);
		return ch;
	}

	~CaseExpr() {
		delete constValue;
		delete stmt;
	}
};

class GotoStmt : public ASTNode {
public:
	ConstValue * address;

	explicit GotoStmt(std::string address) : address(new ConstValue(286, address)) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(address);
		return ch;
	}

	~GotoStmt() {
		delete address;
	}
};

class ExpressionList : public ASTNode {
public:
	ExpressionList * preList;
	Expression * expression;

	explicit ExpressionList(ExpressionList * preList, Expression * expression) : preList(preList), expression(expression) {}

	explicit ExpressionList(Expression * expression) : expression(expression) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(preList);
		ch.emplace_back(expression);
		return ch;
	}

	~ExpressionList() {
		delete preList;
		delete expression;
	}
};

class Expression : public ASTNode {
public:
	std::string binop;
	Expression * expression;
	Expr * expr;

	explicit Expression(Expression * expression, std::string binop, Expr * expr) : expression(expression), binop(std::move(binop)), expr(expr) {}

	explicit Expression(Expr * expr) : expr(expr) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(expression)
			ch.emplace_back(expression);
		ch.emplace_back(expr);
		return ch;
	}

	~Expression() {
		delete expression;
		delete expr;
	}
};

class Expr : public ASTNode {
public:
	std::string binop;
	Expr * expr;
	Term * term;

	explicit Expr(Expr * expr, std::string binop, Term * term) : expr(expr), binop(std::move(binop)), term(term) {}

	explicit Expr(Term * term) : term(term) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(expr)
			ch.emplace_back(expr);
		ch.emplace_back(term);
		return ch;
	}

	~Expr() {
		delete expr;
		delete term;
	}
};

class Term : public ASTNode {
public:
	Term * term;
	std::string binop;
	Factor * factor;

	explicit Term(Term * term, std::string binop, Factor * factor) : term(term), binop(std::move(binop)), factor(factor) {}

	explicit Term(Factor * factor) : factor(factor) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(term)
			ch.emplace_back(term);
		ch.emplace_back(factor);
		return ch;
	}

	~Term() {
		delete term;
		delete factor;
	}
};

class Factor : public ASTNode {
public:
	std::string name, attr, sysFunc;
	ArgsList * argsList;
	ConstValue * constValue;
	Expression * expression;
	Factor * factor;
	bool isMinus, inv = 0;

	explicit Factor(int token, std::string val) {
		if(token == 258) {
			name = std::move(val);
		}else if(token == 282){
			sysFunc = std::move(val);
		}
	}

	explicit Factor(int token, std::string val, ArgsList * argsList) : argsList(argsList) {
		if(token == 258) {
			name = std::move(val);
		}else if(token == 282){
			sysFunc = std::move(val);
		}
	}

	explicit Factor(ConstValue * constValue) : constValue(constValue) {}

	explicit Factor(Expression * expression) : expression(expression) {}

	explicit Factor(int token, Factor * factor) : factor(factor) {
		if(token == 269){
			isMinus = 0;
			inv = 1;
		} else if (token == 271) {
			isMinus = 1;
			inv = 1;
		}
	}

	explicit Factor(std::string name, Expression * expression) : name(std::move(name)), expression(expression) {}

	explicit Factor(std::string name, std::string attr) : name(std::move(name)), attr(std::move(attr)) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		ch.emplace_back(argsList);
		ch.emplace_back(constValue);
		ch.emplace_back(expression);
		ch.emplace_back(factor);
		return ch;
	}

	~Factor() {
		delete argsList;
		delete constValue;
		delete expression;
		delete factor;
	}
};

class ArgsList : public ASTNode {
public:
	ArgsList * preList;
	Expression * expression;

	explicit ArgsList(ArgsList * preList, Expression * expression) : preList(preList), expression(expression) {}

	explicit ArgsList(Expression * expression) : expression(expression) {}

	std::vector<ASTNode *> getChildren() {
		std::vector<ASTNode *> ch = std::vector<ASTNode *>();
		if(preList)
			ch.emplace_back(preList);
		ch.emplace_back(expression);
		return ch;
	}

	~ArgsList() {
		delete preList;
		delete expression;
	}
};

#endif
