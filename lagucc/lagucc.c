#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// トークンの種類
typedef enum
{
	TK_RESERVED, // 記号
	TK_NUM,      // 整数トークン
	TK_EOF,      // 入力の終わりを表す
}						TokenKind;

typedef struct Token	Token;

// トークン型
struct					Token
{
	TokenKind kind; // トークンの型
	Token *next;    // 次の入力トークン
	int val;        // kindがTK_NUMの場合、その数値
	char *str;      // トークン文字列
};

// 入力プログラム
char					*user_input;

// 現在着目しているトークン
Token					*token;

// エラーを報告するための関数
// printfと同じ引数をとる
void	error(char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

// エラー箇所を報告する
void	error_at(char *loc, char *fmt, ...)
{
	va_list	ap;
	int		pos;

	va_start(ap, fmt);
	pos = loc - user_input;
	fprintf(stderr, "%s\n", user_input);
	fprintf(stderr, "%*s", pos, " "); // pos個の空白を出力
	fprintf(stderr, "^ ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

// 次のトークンが期待している記号の時には，トークンを1つ読み進めて真を返す．それ以外は偽を返す．
bool	consume(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
		return (false);
	token = token->next;
	return (true);
}

// 次のトークンが期待している記号の時には，トークンを1つ読み進める．
// それ以外の場合にはエラーを返す．
void	expect(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
		error_at(token->str, "expected '%c'", op);
	token = token->next;
}

// 次のトークンが数値の場合，トークンを1つ読み進めてその数値を返す．
// それ以外の場合はエラーを返す．
int	expect_number(void)
{
	int	val;

	if (token->kind != TK_NUM)
		error_at(token->str, "expected a number");
	val = token->val;
	token = token->next;
	return (val);
}

bool	at_eof(void)
{
	return (token->kind == TK_EOF);
}

// 新しいトークンを作成してcurに繋げる
Token	*new_token(TokenKind kind, Token *cur, char *str)
{
	Token	*tok;

	tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return (tok);
}

// user_inputをトークナイズしてそれを返す
Token	*tokenize(void)
{
	char	*p;
	Token	head;
	Token	*cur;

	p = user_input;
	head.next = NULL;
	cur = &head;
	while (*p)
	{
		// 空白文字をスキップ
		if (isspace(*p))
		{
			p++;
			continue ;
		}
		if (*p == '+' || *p == '-')
		{
			cur = new_token(TK_RESERVED, cur, p++);
			continue ;
		}
		if (isdigit(*p))
		{
			cur = new_token(TK_NUM, cur, p);
			cur->val = strtol(p, &p, 10);
			continue ;
		}
		error_at(p, "invalid token");
	}
	new_token(TK_EOF, cur, p);
	return (head.next);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		error("%s: invalid number of arguments", argv[0]);
		return (1);
	}
	// トークナイズ
	user_input = argv[1];
	token = tokenize();
	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");
	printf("  mov rax, %d\n", expect_number());
	while (!at_eof())
	{
		if (consume('+'))
		{
			printf("  add rax, %d\n", expect_number());
			continue ;
		}
		expect('-');
		printf("  sub rax, %d\n", expect_number());
	}
	printf("  ret\n");
	return (0);
}
