# Expressions in Relay[🔗](https://tvm.apache.org/docs/langref/index.html#)

2020年12月28日

https://blog.csdn.net/weixin_42164269/article/details/103399882

- Dataflow and Control Fragments





 Relay是一种功能多样的编程语言，用于机器学习系统表达的中间表示。relay支持代数数据类型，闭包，控制流和递归，从而可以直接表示比基于计算图的IR更复杂的模型。relay还包括一种使用类型关系的依赖类型的形式，来处理对参数形状有复杂的要求的操作符的形状分析。relay在设计上是可扩展的，这使得机器学习的研究人员和实践者可以很容易地开发新的大型程序转换和优化。

​    以下页面分别描述了relay中的语法，类型系统，代数数据类型和运算符。

- Relay

  中的表达式

  - 数据流和控制片段
  - 变量
  - 函数
  - 操作符
  - 代数数据类型构造器
  - 调用
  - 模块和全局函数
  - 常量
  - 三元组
  - [Let Bindings](https://docs.tvm.ai/langref/relay_expr.html#let-bindings)
  - [Graph Bindings](https://docs.tvm.ai/langref/relay_expr.html#graph-bindings)
  - [If-Then-Else](https://docs.tvm.ai/langref/relay_expr.html#if-then-else)
  - 代数数据类型匹配
  - [TempExprs](https://docs.tvm.ai/langref/relay_expr.html#tempexprs)

- Relay

  的类型系统

  - [Type](https://docs.tvm.ai/langref/relay_type.html#type)
  - [Tensor Type](https://docs.tvm.ai/langref/relay_type.html#tensor-type)
  - [Tuple Type](https://docs.tvm.ai/langref/relay_type.html#tuple-type)
  - [Type Parameter](https://docs.tvm.ai/langref/relay_type.html#type-parameter)
  - [Type Constraint](https://docs.tvm.ai/langref/relay_type.html#type-constraint)
  - [Function Type](https://docs.tvm.ai/langref/relay_type.html#function-type)
  - [Type Relation](https://docs.tvm.ai/langref/relay_type.html#type-relation)
  - [Incomplete Type](https://docs.tvm.ai/langref/relay_type.html#incomplete-type)
  - [Algebraic Data Types](https://docs.tvm.ai/langref/relay_type.html#algebraic-data-types)

- R

  elay中的代数数据类型

  - [Defining and Matching on an ADT](https://docs.tvm.ai/langref/relay_adt.html#defining-and-matching-on-an-adt)
  - [Type-Checking ADTs and Polymorphism](https://docs.tvm.ai/langref/relay_adt.html#type-checking-adts-and-polymorphism)
  - [Recursion with ADTs](https://docs.tvm.ai/langref/relay_adt.html#recursion-with-adts)
  - [Pattern Matching in Match Expressions](https://docs.tvm.ai/langref/relay_adt.html#pattern-matching-in-match-expressions)
  - [Common ADT Uses](https://docs.tvm.ai/langref/relay_adt.html#common-adt-uses)
  - [Implementing Neural Nets Using ADTs](https://docs.tvm.ai/langref/relay_adt.html#implementing-neural-nets-using-adts)

- Relay

  核张量操作符

  - [Overview of Operators](https://docs.tvm.ai/langref/relay_op.html#overview-of-operators)
  - [Level 1 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-1-definitions)
  - [Level 2 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-2-definitions)
  - [Level 3 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-3-definitions)
  - [Level 4 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-4-definitions)
  - [Level 5 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-5-definitions)
  - [Level 6 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-6-definitions)
  - [Level 10 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-10-definitions)
  - [Level 11 Definitions](https://docs.tvm.ai/langref/relay_op.html#level-11-definitions)

----

The Relay IR is a pure, expression-oriented language. The below sections describe the different expressions in Relay and give details of their semantics.

Relay IR是一种纯粹的面向表达式的语言。以下各节描述了Relay中的不同表达式，并提供了其语义的详细信息



## 1. Dataflow and Control Fragments

For the purposes of comparing Relay to traditional computational graph-based IRs, it can be useful to consider Relay expressions in terms of dataflow and control fragments. Each portion of a Relay program containing expressions that only affect the dataflow can be viewed as a traditional computation graph when writing and expressing transformations.

为了将Relay与传统的基于计算图的IR进行比较，从数据流和控制片段的角度考虑Relay表达式可能会很有用。编写和表示转换时，包含仅影响数据流的表达式的Relay程序的每个部分都可以视为传统的计算图。



The dataflow fragment covers the set of Relay expressions that do not involve control flow. That is, any portion of a program containing only the following constructs corresponds to a pure computation graph:

数据流片段涵盖了不涉及控制流的一组中继表达式。也就是说，仅包含以下构造的程序的任何部分都对应于纯计算图：



