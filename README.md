## Introduction
miniob设计的目标是让不熟悉数据库设计和实现的同学能够快速的了解与深入学习数据库内核，期望通过miniob相关训练之后，能够对各个数据库内核模块的功能与它们之间的关联有所了解，并能够在
使用时，设计出高效的SQL。面向的对象主要是在校学生，并且诸多模块做了简化，比如不考虑并发操作。
注意：此代码仅供学习使用，不考虑任何安全特性。

# How to build
please refer to docs/how_to_build.md

# 进度
[题目](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-topics)
- [x] 优化buffer pool
- [x] 查询元数据校验(select-meta)
- [x] drop table(drop-table)
- [x] 实现update功能(update)
- [x] 增加date字段(date)
- [x] 多表查询(select-tables)
- [x] 聚合运算(aggregation-func)
- [x] 多表join操作(join-tables)
- [x] 一次插入多条数据(insert)
- [x] 唯一索引(unique)
- [x] 支持NULL类型(null)
- [ ] 简单子查询(simple-sub-query)
- [ ] 多列索引(multi-index)
- [x] 超长字段(text)
- [ ] 查询支持表达式(expression)
- [ ] 复杂子查询(complex-sub-query)
- [x] 排序(order-by)
- [x] 分组(group-by)
