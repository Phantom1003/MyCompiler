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
	ASTNode();

	// virtual llvm::Value * codeGen(CodeGenContext &context) {
	// 	return 0;
	// }
	virtual std::vector<ASTNode *> getChildren();
	virtual std::string getName();
	virtual ~ASTNode();

};

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

	explicit Program(ProgramHead *programHead, Routine *routine);
	
	std::vector<ASTNode *> getChildren();

	~Program();
};

class ProgramHead : public ASTNode {
public:
	std::string name;

	explicit ProgramHead(std::string name);

	std::vector<ASTNode *> getChildren();

	std::string getName();
};

class Routine : public ASTNode {
public:
	RoutineHead * routineHead;
	RoutineBody * routineBody;

	explicit Routine(RoutineHead *routineHead, RoutineBody * routineBody);

	std::vector<ASTNode *> getChildren();
	~Routine();
};

class SubRoutine : public ASTNode {
public:
	RoutineHead * routineHead;
	RoutineBody * routineBody;

	explicit SubRoutine(RoutineHead *routineHead, RoutineBody * routineBody);

	std::vector<ASTNode *> getChildren();
	~SubRoutine();
};

class RoutineHead : public ASTNode {
public:
	LabelPart * labelPart;
	ConstPart * constPart;
	TypePart * typePart;
	VarPart * varPart;
	RoutinePart * routinePart;

	explicit RoutineHead(LabelPart *labelPart, ConstPart *constPart, TypePart *typePart, VarPart *varPart, RoutinePart *routinePart);

	std::vector<ASTNode *> getChildren();
    ~RoutineHead();
};

class LabelPart : public ASTNode {
public:

	std::vector<ASTNode *> getChildren();
};

class ConstPart : public ASTNode {
public:
	ConstExprList * constExprList;

	explicit ConstPart(ConstExprList *constExprList);
	explicit ConstPart();

	std::vector<ASTNode *> getChildren();
	~ConstPart();
};

class ConstExprList : public ASTNode {
public:
	std::string name;
	ConstExprList * preList;
	ConstValue * constValue;

	explicit ConstExprList(std::string name, ConstExprList *preList, ConstValue * constValue);

	explicit ConstExprList(std::string name, ConstValue * constValue);

	std::vector<ASTNode *> getChildren();
	~ConstExprList();
};

class ConstValue : public ASTNode {
public:
	int token;
	std::string value;

	explicit ConstValue(int token, std::string value);

	std::vector<ASTNode *> getChildren();

	ConstValue * neg();
};

class TypePart : public ASTNode {
public:
	TypeDeclList * typeDeclList;

	explicit TypePart(TypeDeclList * typeDeclList);

	TypePart();

	std::vector<ASTNode *> getChildren();
};

class TypeDeclList : public ASTNode {
public:
	TypeDeclList * preList;
	TypeDefinition * typeDefinition;

	explicit TypeDeclList(TypeDeclList * preList, TypeDefinition * typeDefinition);
	
	explicit TypeDeclList(TypeDefinition * typeDefinition);

	std::vector<ASTNode *> getChildren();
};

class TypeDefinition : public ASTNode {
public:
	std::string name;
	TypeDecl * typeDecl;

	explicit TypeDefinition(std::string name, TypeDecl * typeDecl);
	
	std::vector<ASTNode *> getChildren();

	std::string getName();
};

class TypeDecl : public ASTNode {
public:
	SimpleTypeDecl * simpleTypeDecl;
	ArrayTypeDecl * arrayTypeDecl;
	RecordTypeDecl * recordTypeDecl;

	explicit TypeDecl(SimpleTypeDecl * simpleTypeDecl);

	explicit TypeDecl(ArrayTypeDecl * arrayTypeDecl);
	
	explicit TypeDecl(RecordTypeDecl * recordTypeDecl);

	std::vector<ASTNode *> getChildren();

	~TypeDecl();
};

class SimpleTypeDecl : public ASTNode {
public:
	std::string sysType;
	std::string name;

	NameList * nameList;
	ConstValue * lowerValue, * upperValue;
	std::string lowerName, upperName;

	explicit SimpleTypeDecl(int token, std::string value);

	explicit SimpleTypeDecl(NameList * nameList);

	explicit SimpleTypeDecl(ConstValue * lowerValue, ConstValue * upperValue);

	explicit SimpleTypeDecl(std::string lowerName, std::string upperName);

	std::vector<ASTNode *> getChildren();
	~SimpleTypeDecl();
};

class ArrayTypeDecl : public ASTNode {
public:
	SimpleTypeDecl * simpleTypeDecl;
	TypeDecl * typeDecl;

	explicit ArrayTypeDecl(SimpleTypeDecl * simpleTypeDecl, TypeDecl * typeDecl);

	std::vector<ASTNode *> getChildren();

	~ArrayTypeDecl();
};

class RecordTypeDecl : public ASTNode {
public:
	FieldDeclList * fieldDeclList;

	explicit RecordTypeDecl(FieldDeclList * fieldDeclList);

	std::vector<ASTNode *> getChildren();

	~RecordTypeDecl();
};

class FieldDeclList : public ASTNode {
public:
	FieldDeclList * preList;
	FieldDecl * fieldDecl;

	explicit FieldDeclList(FieldDeclList * preList, FieldDecl * fieldDecl);

	explicit FieldDeclList(FieldDecl * fieldDecl);

	std::vector<ASTNode *> getChildren();

	~FieldDeclList();
};

class FieldDecl : public ASTNode {
public:
	NameList * nameList;
	TypeDecl * typeDecl;

	explicit FieldDecl(NameList * nameList, TypeDecl * typeDecl);

	std::vector<ASTNode *> getChildren();

	~FieldDecl();
};

class NameList : public ASTNode {
public:
	NameList * preList;
	std::string name;

	explicit NameList(std::string name, NameList * preList);

	explicit NameList(std::string name);

	std::vector<ASTNode *> getChildren();

	std::string getName();

	~NameList();
};

class VarPart : public ASTNode {
public:
	VarDeclList * varDeclList;

	explicit VarPart(VarDeclList * varDeclList);

	VarPart();

	std::vector<ASTNode *> getChildren();

	~VarPart();
};

class VarDeclList : public ASTNode {
public:
	VarDeclList * preList;
	VarDecl * varDecl;

	explicit VarDeclList(VarDeclList * preList, VarDecl * varDecl);

	explicit VarDeclList(VarDecl * varDecl);

	std::vector<ASTNode *> getChildren();

	~VarDeclList();
};

class VarDecl : public ASTNode {
public:
	NameList * nameList;
	TypeDecl * typeDecl;

	explicit VarDecl(NameList * nameList, TypeDecl * typeDecl);

	std::vector<ASTNode *> getChildren();

	~VarDecl();
};

class RoutinePart : public ASTNode {
public:
	RoutinePart * prePart;
	FunctionDecl * functionDecl;
	ProcedureDecl * procedureDecl;

	explicit RoutinePart(RoutinePart * prePart, FunctionDecl * functionDecl);

	explicit RoutinePart(RoutinePart * prePart, ProcedureDecl * procedureDecl);

	explicit RoutinePart(FunctionDecl * functionDecl);

	explicit RoutinePart(ProcedureDecl * procedureDecl);

	RoutinePart();

	std::vector<ASTNode *> getChildren();

	~RoutinePart();
};

class FunctionDecl : public ASTNode {
public:
	FunctionHead * functionHead;
	SubRoutine * subRoutine;

	explicit FunctionDecl(FunctionHead * functionHead, SubRoutine * subRoutine);

	std::vector<ASTNode *> getChildren();

	~FunctionDecl();
};

class FunctionHead : public ASTNode {
public:
	std::string name;
	Parameters * parameters;
	SimpleTypeDecl * simpleTypeDecl;

	explicit FunctionHead(std::string name, Parameters * parameters, SimpleTypeDecl * simpleTypeDecl);

	std::vector<ASTNode *> getChildren();

	std::string getName();

	~FunctionHead();
};

class ProcedureDecl : public ASTNode {
public:
	ProcedureHead * procedureHead;
	SubRoutine * subRoutine;

	explicit ProcedureDecl(ProcedureHead * procedureHead, SubRoutine * subRoutine);

	std::vector<ASTNode *> getChildren();

	~ProcedureDecl();
};

class ProcedureHead : public ASTNode {
public:
	Parameters * parameters;
	std::string name;

	explicit ProcedureHead(std::string name, Parameters * parameters);

	std::vector<ASTNode *> getChildren();

	~ProcedureHead();
};

class Parameters : public ASTNode {
public:
	ParaDeclList * paraDeclList;

	explicit Parameters(ParaDeclList * paraDeclList);
	explicit Parameters();

	std::vector<ASTNode *> getChildren();

	~Parameters();
};

class ParaDeclList : public ASTNode {
public:
	ParaDeclList * preList;
	ParaTypeList * paraTypeList;

	explicit ParaDeclList(ParaDeclList * preList, ParaTypeList * paraTypeList);

	explicit ParaDeclList(ParaTypeList * paraTypeList);

	std::vector<ASTNode *> getChildren();
};

class ParaTypeList : public ASTNode {
public:
	VarParaList * varParaList;
	ValParaList * valParaList;
	SimpleTypeDecl * simpleTypeDecl;

	explicit ParaTypeList(VarParaList * varParaList, SimpleTypeDecl * simpleTypeDecl);

	explicit ParaTypeList(ValParaList * valParaList, SimpleTypeDecl * simpleTypeDecl);

	std::vector<ASTNode *> getChildren();

	~ParaTypeList();
};

class VarParaList : public ASTNode {
public:
	NameList * nameList;

	explicit VarParaList(NameList * nameList);

	std::vector<ASTNode *> getChildren();

	~VarParaList();
};

class ValParaList : public ASTNode {
public:
	NameList * nameList;

	explicit ValParaList(NameList * nameList);

	std::vector<ASTNode *> getChildren();

	~ValParaList();
};

class RoutineBody : public ASTNode {
public:
	CompoundStmt * compoundStmt;

	explicit RoutineBody(CompoundStmt * compoundStmt);

	std::vector<ASTNode *> getChildren();

	~RoutineBody();
};

class CompoundStmt : public ASTNode {
public:
	StmtList * stmtList;

	explicit CompoundStmt(StmtList * stmtList);

	std::vector<ASTNode *> getChildren();

	~CompoundStmt();
};

class StmtList : public ASTNode {
public:
	StmtList * preList;
	Stmt * stmt;

	explicit StmtList(StmtList * preList, Stmt * stmt);

	explicit StmtList();

	std::vector<ASTNode *> getChildren();

	~StmtList();
};

class Stmt : public ASTNode {
public:
	std::string label;
	NonLabelStmt * nonLabelStmt;

	explicit Stmt(std::string label, NonLabelStmt * nonLabelStmt);

	explicit Stmt(NonLabelStmt * nonLabelStmt);

	std::vector<ASTNode *> getChildren();

	~Stmt();
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

	explicit NonLabelStmt(AssignStmt * assignStmt);

	explicit NonLabelStmt(ProcStmt * procStmt);
	
	explicit NonLabelStmt(CompoundStmt * compoundStmt);
	
	explicit NonLabelStmt(IfStmt * ifStmt);
	
	explicit NonLabelStmt(RepeatStmt * repeatStmt);
	
	explicit NonLabelStmt(WhileStmt * whileStmt);
	
	explicit NonLabelStmt(ForStmt * forStmt);
	
	explicit NonLabelStmt(CaseStmt * caseStmt);
	
	explicit NonLabelStmt(GotoStmt * gotoStmt);

	std::vector<ASTNode *> getChildren();
	
	~NonLabelStmt();
};

class AssignStmt : public ASTNode {
public:
	std::string name, attr;
	Expression * expression, * index;

	explicit AssignStmt(std::string name, Expression * expression);

	explicit AssignStmt(std::string name, Expression * index, Expression * expression);

	explicit AssignStmt(std::string name, std::string attr, Expression * expression);

	std::vector<ASTNode *> getChildren();

	~AssignStmt();
};

class ProcStmt : public ASTNode {
public:
	std::string name, sysProc;
	ArgsList * argsList;
	ExpressionList * expressionList;
	Factor * factor;

	explicit ProcStmt(bool isSysProc, std::string val);

	explicit ProcStmt(std::string name, ArgsList * argsList);

	explicit ProcStmt(std::string sysProc, ExpressionList * expressionList);

	explicit ProcStmt(Factor * factor);

	std::vector<ASTNode *> getChildren();

	~ProcStmt();
};

class IfStmt : public ASTNode {
public:
	Expression * expression;
	Stmt * stmt;
	ElseClause * elseClause;

	explicit IfStmt(Expression * expression, Stmt * stmt, ElseClause * elseClause);

	std::vector<ASTNode *> getChildren();

	~IfStmt();
};

class ElseClause : public ASTNode {
public:
	Stmt * stmt;

	explicit ElseClause(Stmt * stmt);

	ElseClause();

	std::vector<ASTNode *> getChildren();

	~ElseClause();
};

class RepeatStmt : public ASTNode {
public:
	StmtList * stmtList;
	Expression * expression;

	explicit RepeatStmt(StmtList * stmtList, Expression * expression);

	std::vector<ASTNode *> getChildren();

	~RepeatStmt();
};

class WhileStmt : public ASTNode {
public:
	Expression * expression;
	Stmt * stmt;

	explicit WhileStmt(Expression * expression, Stmt * stmt);

	std::vector<ASTNode *> getChildren();

	~WhileStmt();
};

class ForStmt : public ASTNode {
public:
	std::string name;
	Expression * expr1, * expr2;
	Direction * direction;
	Stmt * stmt;

	explicit ForStmt(std::string name, Expression * expr1, Direction * direction, Expression * expr2, Stmt * stmt);

	std::vector<ASTNode *> getChildren();

	~ForStmt();
};

class Direction : public ASTNode {
public:
	std::string dir;

	explicit Direction(std::string dir);

	std::vector<ASTNode *> getChildren();
};

class CaseStmt : public ASTNode {
public:
	Expression * expression;
	CaseExprList * caseExprList;

	explicit CaseStmt(Expression * expression, CaseExprList * caseExprList);

	std::vector<ASTNode *> getChildren();

	~CaseStmt();
};

class CaseExprList : public ASTNode {
public:
	CaseExprList * preList;
	CaseExpr * caseExpr;

	explicit CaseExprList(CaseExprList * preList, CaseExpr * caseExpr);

	explicit CaseExprList(CaseExpr * caseExpr);

	std::vector<ASTNode *> getChildren();

	~CaseExprList();
};

class CaseExpr : public ASTNode {
public:
	std::string name;
	ConstValue * constValue;
	Stmt * stmt;

	explicit CaseExpr(ConstValue * constValue, Stmt * stmt);

	explicit CaseExpr(std::string name, Stmt * stmt);

	std::vector<ASTNode *> getChildren();

	~CaseExpr();
};

class GotoStmt : public ASTNode {
public:
	ConstValue * address;

	explicit GotoStmt(std::string address);

	std::vector<ASTNode *> getChildren();

	~GotoStmt();
};

class ExpressionList : public ASTNode {
public:
	ExpressionList * preList;
	Expression * expression;

	explicit ExpressionList(ExpressionList * preList, Expression * expression);

	explicit ExpressionList(Expression * expression);

	std::vector<ASTNode *> getChildren();

	~ExpressionList();
};

class Expression : public ASTNode {
public:
	std::string binop;
	Expression * expression;
	Expr * expr;

	explicit Expression(Expression * expression, std::string binop, Expr * expr);

	explicit Expression(Expr * expr);

	std::vector<ASTNode *> getChildren();

	~Expression();
};

class Expr : public ASTNode {
public:
	std::string binop;
	Expr * expr;
	Term * term;

	explicit Expr(Expr * expr, std::string binop, Term * term);

	explicit Expr(Term * term);

	std::vector<ASTNode *> getChildren();

	~Expr();
};

class Term : public ASTNode {
public:
	Term * term;
	std::string binop;
	Factor * factor;

	explicit Term(Term * term, std::string binop, Factor * factor);

	explicit Term(Factor * factor);

	std::vector<ASTNode *> getChildren();

	~Term();
};

class Factor : public ASTNode {
public:
	std::string name, attr, sysFunc;
	ArgsList * argsList;
	ConstValue * constValue;
	Expression * expression;
	Factor * factor;
	bool isMinus, inv;

	explicit Factor(int token, std::string val);

	explicit Factor(int token, std::string val, ArgsList * argsList);

	explicit Factor(ConstValue * constValue);

	explicit Factor(Expression * expression);

	explicit Factor(int token, Factor * factor);

	explicit Factor(std::string name, Expression * expression);

	explicit Factor(std::string name, std::string attr);

	std::vector<ASTNode *> getChildren();

	~Factor();
};

class ArgsList : public ASTNode {
public:
	ArgsList * preList;
	Expression * expression;

	explicit ArgsList(ArgsList * preList, Expression * expression);

	explicit ArgsList(Expression * expression);

	std::vector<ASTNode *> getChildren();

	~ArgsList();
};

#endif
