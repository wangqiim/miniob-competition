
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;

  Selects selects[MAX_NUM];
  size_t select_length;

  RelAttr attrs[MAX_NUM][MAX_NUM];
  size_t attr_length[MAX_NUM];

  Aggregate aggregates[MAX_NUM][MAX_NUM];
//  size_t aggre_length[MAX_NUM];
  AggreType aggreType[MAX_NUM];

  char *  relations[MAX_NUM][MAX_NUM];
  size_t from_length[MAX_NUM];

  Join joins[MAX_NUM][MAX_NUM];
  size_t join_length[MAX_NUM];

  Condition join_conditions[MAX_NUM][MAX_NUM];
  size_t join_condition_length[MAX_NUM];

  Condition conditions[MAX_NUM][MAX_NUM];
  size_t condition_length[MAX_NUM];

  Selects left_sub_select;
  Selects right_sub_select;

  size_t value_length;
  Value values[MAX_NUM];
  size_t insert_pair_num;
  CompOp comp[MAX_NUM];
  char id[MAX_NUM];
  int order; //0: asc, 1: desc
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  // 提前分配一个超过12字节的内存空间用来存放整个日期"xxxx-xx-xx"
  int len = sizeof(char) * (n2 - n1 + 2);
  if (len < 12) {
  	len = 12;
  }
  char *sp = malloc(len);
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length[0] = 0;
  context->from_length[0] = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.pair_num = 0;
//  context->aggre_length = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
		UNIQUE
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
		DATE_T
		TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        INNER
        JOIN
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
		MAX_T
		MIN_T
		AVG_T
		SUM_T
		COUNT_T
        EQ
        LT
        GT
        LE
        GE
        NE
		NOT_T
		NULL_T
		NULLABLE_T
		IS_T
		ORDER
		BY
		ASC
		IN
		GROUP
		ADD
		SUB
		DIV

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;
  struct ast *ast1;
}

%left ADD SUB
%left STAR DIV

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;
%type <ast1> exp

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select_clause
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, 0, $3, $5);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $7);
		}
	| CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";(unique)
			create_index_init(&CONTEXT->ssql->sstr.create_index, 1, $4, $6);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $8);
		}
    ;

id_list:
	/* empty */
	| COMMA ID id_list {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $2);
	}
	;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type
		{
			// default: not null
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0); // TODO(wq): 第4个参数不应该写死是4吧,会导致字符串被截断
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    |ID_get type NOT_T NULL_T
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    |ID_get type NULLABLE_T
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    ;

number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
	   | DATE_T { $$=DATES; }
	   | TEXT_T { $$=TEXTS; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_pair_list SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3);

			//临时变量清零
			CONTEXT->insert_pair_num=0;
			CONTEXT->value_length=0;
    }

value_list:
    /* empty */ {
		// TODO(wq): 插入数据
		// 递增pair_num, 清零value_length
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->insert_pair_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
    ;

insert_pair_list:
	/* empty */
	| COMMA LBRACE value value_list RBRACE insert_pair_list {
		}
	;

value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
  		$$ = &CONTEXT->values[CONTEXT->value_length - 1];
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
  		$$ = &CONTEXT->values[CONTEXT->value_length - 1];
		}
    |SSS {
  		$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
  		$$ = &CONTEXT->values[CONTEXT->value_length - 1];
		}
	|NULL_T {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
  		$$ = &CONTEXT->values[CONTEXT->value_length - 1];
		}
    ;

exp:
	exp ADD exp { $$ = newast(ADDN, $1, $3); }
	| SUB exp { $$ = newast(SUBN, NULL, $2); }
	| exp SUB exp { $$ = newast(SUBN, $1, $3); }
	| exp STAR exp { $$ = newast(MULN, $1, $3); }
	| exp DIV exp { $$ = newast(DIVN, $1, $3); }
	| LBRACE exp RBRACE {
		ast *a = (ast *)$2;
		a->l_brace++;
		a->r_brace++;
		$$ = $2;
	} 
	| value { $$ = newvalNode($1); }
	| ID {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		$$ = newattrNode(&attr);
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		$$ = newattrNode(&attr);
	}
	| ID DOT STAR {
		RelAttr attr;
		relation_attr_init(&attr, $1, "*");
		$$ = newattrNode(&attr);
	}
	;

delete_begin:
    DELETE {
    	CONTEXT->select_length++;
    }
    ;

delete:		/*  delete 语句的语法解析树*/
    delete_begin FROM ID where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
    }
    ;

update_begin:
   UPDATE {
   	CONTEXT->select_length++;
   }
   ;

update:			/*  update 语句的语法解析树*/
    update_begin ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
		}
    ;

select_begin:
    SELECT {
    	CONTEXT->select_length++;
    	clear_selects(&CONTEXT->selects[CONTEXT->select_length-1]);
    }
    ;

select_end:
    /* empty */
    ;

select_clause:
	select SEMICOLON {
		// 解决 shift/reduce冲突
	}
	;

select:				/*  select 语句的语法解析树*/
    select_begin select_attr FROM ID rel_list inner_join_list where group_by order_by select_end
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], $4);

			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->conditions[CONTEXT->select_length-1], CONTEXT->condition_length[CONTEXT->select_length-1]);

			selects_append_joins(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->joins[CONTEXT->select_length-1], CONTEXT->join_length[CONTEXT->select_length-1]);

			//临时变量清零
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length-1];
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			CONTEXT->condition_length[CONTEXT->select_length-1]=0;
			CONTEXT->from_length[CONTEXT->select_length-1]=0;
			CONTEXT->value_length = 0;
			CONTEXT->join_length[CONTEXT->select_length-1]=0;
    			show_selects(CONTEXT->selects, CONTEXT->select_length-1);
    			CONTEXT->select_length--;
	}
	;

select_attr:
    STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
	| exp attr_list {
		selects_append_attribute_expression(&CONTEXT->selects[CONTEXT->select_length-1], $1);
	}
	| aggre_func attr_list
    ;

attr_list:
    /* empty */
    | COMMA exp attr_list {
		selects_append_attribute_expression(&CONTEXT->selects[CONTEXT->select_length-1], $2);
    }
  	| COMMA aggre_func attr_list
	;

aggre_func:
	aggre_type LBRACE value RBRACE {
		Aggregate aggre;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 0, NULL, NULL, value);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
	| aggre_type LBRACE ID RBRACE {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, $3, NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
	| aggre_type LBRACE ID DOT ID RBRACE {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, $3, $5, NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
	| aggre_type LBRACE STAR RBRACE {
		// TODO(wq):仅需要支持 select COUNT(*)，不需要支持select other_aggre(*) 以及select aggre_func(table_name.*);
		// 由于如果在语法解析里处理该问题的话，代码写的比较冗余丑陋，所以这里不检查sum(*)等这种不合法情况，丢给parse之后的stage去检验
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, "*", NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	}
	;

aggre_type:
	  MAX_T { CONTEXT->aggreType[CONTEXT->select_length-1] = MAXS; }
	| MIN_T { CONTEXT->aggreType[CONTEXT->select_length-1] = MINS; }
	| AVG_T { CONTEXT->aggreType[CONTEXT->select_length-1] = AVGS; }
	| SUM_T { CONTEXT->aggreType[CONTEXT->select_length-1] = SUMS; }
	| COUNT_T { CONTEXT->aggreType[CONTEXT->select_length-1] = COUNTS; }
	;

rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], $2);
		  }
    ;

inner_join:
    INNER JOIN ID ON join_condition join_condition_list {
    	Join join;
    	join_init(&join, INNER_JOIN, $3, CONTEXT->join_conditions[CONTEXT->select_length-1], CONTEXT->join_condition_length[CONTEXT->select_length-1]);
    	CONTEXT->joins[CONTEXT->select_length-1][CONTEXT->join_length[CONTEXT->select_length-1]++] = join;
    	// 清空变量
    	CONTEXT->join_condition_length[CONTEXT->select_length-1] = 0;
    }
    ;

inner_join_list:
    /* empty */
    | inner_join inner_join_list  {

    }
    ;

join_condition_list:
     /* empty */
     | AND join_condition join_condition_list {

     }
     ;
join_condition:
    exp comOp exp {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], $1, $3, NULL, NULL);
		CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->join_condition_length[CONTEXT->select_length-1]++] = condition;
    }
    | exp comOp right_sub_select {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], $1, NULL, NULL, &CONTEXT->right_sub_select);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    	}
    | left_sub_select comOp exp {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, $3, &CONTEXT->left_sub_select, NULL);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
        }
    |  left_sub_select comOp right_sub_select {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, NULL,  &CONTEXT->left_sub_select, &CONTEXT->right_sub_select);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
    ;

where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;

condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;

condition:
    exp comOp exp {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], $1, $3, NULL, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
    | exp comOp right_sub_select {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], $1, NULL, NULL, &CONTEXT->right_sub_select);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
    | left_sub_select comOp exp {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, $3, &CONTEXT->left_sub_select, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
    | left_sub_select comOp right_sub_select {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, NULL, &CONTEXT->left_sub_select, &CONTEXT->right_sub_select);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
    ;

left_sub_select:
    LBRACE select RBRACE {
    	CONTEXT->left_sub_select = CONTEXT->selects[CONTEXT->select_length];
    }
    ;

right_sub_select:
    LBRACE select RBRACE {
    	CONTEXT->right_sub_select = CONTEXT->selects[CONTEXT->select_length];
    }
    ;

comOp:
  	  EQ { CONTEXT->comp[CONTEXT->select_length-1] = EQUAL_TO; }
    | LT { CONTEXT->comp[CONTEXT->select_length-1] = LESS_THAN; }
    | GT { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_THAN; }
    | LE { CONTEXT->comp[CONTEXT->select_length-1] = LESS_EQUAL; }
    | GE { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_EQUAL; }
    | NE { CONTEXT->comp[CONTEXT->select_length-1] = NOT_EQUAL; }
	| IS_T { CONTEXT->comp[CONTEXT->select_length-1] = IS; }
	| IS_T NOT_T { CONTEXT->comp[CONTEXT->select_length-1] = IS_NOT; }
   | IN { CONTEXT->comp[CONTEXT->select_length-1] = IN_OP; }
   | NOT_T IN { CONTEXT->comp[CONTEXT->select_length-1] = NOT_IN_OP; }
    ;

order_by:
    /* empty */
	| ORDER BY order_item order_item_list
	;

order_item:
	ID order {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
	| ID DOT ID order {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
	;

order:
	/* empty */ {
		CONTEXT->order = 0;
	}
	| ASC {
		CONTEXT->order = 0;
	}
	| DESC {
		CONTEXT->order = 1;
	}
	;

order_item_list:
	/* empty */
	| COMMA order_item order_item_list
	;

group_by:
	/* empty */
	| GROUP BY group_item group_item_list
	;

group_item:
	ID {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	;

group_item_list:
	/* empty */
	| COMMA group_item group_item_list
	;


load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
