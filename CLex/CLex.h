/*
 *
 *       Filename:  CLexAnalyzer.h
 *        Created:  03/09/2014 17:39:04
 *         Author:  Leo Lee (), leeleo3x@gmail.com
 *
 */

#define AUTO 1
#define BREAK 2
#define CASE 3
#define CHAR 4
#define CONST 5
#define CONTINUE 6
#define DEFAULT 7
#define DO 8
#define DOUBLE 9
#define ELSE 10
#define ENUM 11
#define EXTERN 12
#define FLOAT 13
#define FOR 14
#define GOTO 15
#define IF 16
#define INT 17
#define LONG 18
#define REGISTER 19
#define RETURN 20
#define SHORT 21
#define SIGNED 22
#define SIZEOF 23
#define STATIC 24
#define STRUCT 25
#define SWITCH 26
#define TYPEDEF 27
#define UNION 28
#define UNSIGNED 29
#define VOID 30
#define VOLATILE 31
#define WHILE 32
#define KEY_DESC "关键字"

//标志符
#define IDENTIFIER 40
#define IDENTIFIER_DESC "标志符"
#define IDENTIFIER_DEFINATION 41
#define IDENTIFIER_DEFINATION_DESC "声明标示符"

//常量
#define INT_VAL 51 //整形常量
#define CHAR_VAL 52 //字符常量
#define FLOAT_VAL 53 //浮点数常量
#define STRING_VAL 54 //双精度浮点数常量
#define MACRO_VAL 55 //宏常量
#define CONSTANT_DESC "常量"

//运算符
#define NOT 61   // !
#define BYTE_AND 62 //&
#define COMPLEMENT 63 // ~
#define BYTE_XOR  64 // ^
#define MUL 65 // *
#define DIV 66// /
#define MOD 67 // %
#define ADD 68 // +
#define SUB 69 // -
#define LES_THAN 70 // <
#define GRT_THAN 71 // >
#define ASG 72 // =
#define ARROW 73 // ->
#define SELF_ADD 74 // ++
#define SELF_SUB 75 // --
#define LEFT_MOVE 76 // <<
#define RIGHT_MOVE 77 // >>
#define LES_EQUAL 78 // <=
#define GRT_EQUAL 79 // >=
#define EQUAL 80 // ==
#define NOT_EQUAL 81 // !=
#define AND 82 // &&
#define OR 83 // ||
#define COMPLETE_ADD 84 // +=
#define COMPLETE_SUB 85 // -=
#define COMPLETE_MUL 86 // *=
#define COMPLETE_DIV 87 // /=
#define COMPLETE_BYTE_XOR 88 // ^=
#define COMPLETE_BYTE_AND 89 // &=
#define COMPLETE_COMPLEMENT 90 // ~=
#define COMPLETE_MOD 91 //%=
#define BYTE_OR 92 // |

#define OPE_DESC "运算符"

//限界符
#define LEFT_BRA 100 // (
#define RIGHT_BRA 101 // )
#define LEFT_INDEX 102 // [
#define RIGHT_INDEX 103 // ]
#define L_BOUNDER 104 //  {
#define R_BOUNDER 105 // }
#define POINTER 106 // .
#define JING 107 // #
#define UNDER_LINE 108 // _
#define COMMA 109 // ,
#define SEMI 110 // ;
#define SIN_QUE 111 // '
#define DOU_QUE 112 // "
#define SPACE 113

#define CLE_OPE_DESC "限界符"

#define NOTE1 120 // "/**/"注释
#define NOTE2 121 // "//"注释
#define NOTE_DESC "注释"


#define HEADER 130 //头文件
#define HEADER_DESC "头文件"

//错误类型
#define FLOAT_ERROR "float expression error"
#define FLOAT_ERROR_NUM 1
#define DOUBLE_ERROR "double expression error"
#define DOUBLE_ERROR_NUM 2
#define NOTE_ERROR "comments without ending"
#define NOTE_ERROR_NUM 3
#define STRING_ERROR "string without ending"
#define STRING_ERROR_NUM 4
#define CHARCONST_ERROR "char without ending"
#define CHARCONST_ERROR_NUM 5
#define CHAR_ERROR "illegal charactor"
#define CHAR_ERROR_NUM 6
#define LEFT_BRA_ERROR "'('not matching"
#define LEFT_BRA_ERROR_NUM 7
#define RIGHT_BRA_ERROR "')'not matching"
#define RIGHT_BRA_ERROR_NUM 8
#define LEFT_INDEX_ERROR "'['not matching"
#define LEFT_INDEX_ERROR_NUM 9
#define RIGHT_INDEX_ERROR "']'not matching"
#define RIGHT_INDEX_ERROR_NUM 10
#define L_BOUNDER_ERROR "'{'not matching"
#define L_BOUNDER_ERROR_NUM 11
#define R_BOUNDER_ERROR "'}'not matching"
#define R_BOUNDER_ERROR_NUM 12
#define PRE_PROCESS_ERROR "preprocessing error" //头文件或者宏定义错误
#define PRE_PROCESS_ERROR_NUM  13
#define UNDEFINED_IDENTIFIER "undefined identifier"
#define UNDEFINED_IDENTIFIER_NUM 14
#define UNUSED_IDENTIFIER "unused identifier"
#define UNUSED_IDENTIFIER_NUM 15

#define _NULL ""

#define DESCRIBE 4000
#define TYPE 4001
#define STRING 4002
#define DIGIT 4003

struct normalNode
{
    char * content;//内容
    char * describe;//描述
    int type;//种别码
    int addr;//入口地址
    int line;//所在行数
    struct normalNode * next, * pre;//下一个节点
};

struct errorNode
{
    char * content;
    char * describe;
    int type;
    int line;
    struct errorNode *next;
};

struct identifierNode
{
    char * content;
    char * describe;
    int type;
    int addr;
    int line;
    struct identifierNode * next, * pre;
};


