# C、C++和C#区别概述

2020年7月29日，原文地址见末尾

---

今天突然好奇C、C++和C#这三门语言都有个C，那么它们之间到底有什么关联呢。所以就去Google了，找到了这篇文章：[Understanding the Differences Between C#, C++, and C - C# Station](https://csharp-station.com/understanding-the-differences-between-c-c-and-c/)。看完感觉写得挺好的，就打算翻译出来。

需要注意的是，本人技术十分有限，从事的也并不是编程相关的工作，因此翻译的准确性可能有待商榷，建议有英语基础的同学，可直接阅读源站。

##  1. 开始

如果你是一个有志向的程序员，那么你可能会很难决定先学哪门编程语言。世界上有相当多的编程语言，但是在C、C++和C#中哪一个是最有用的呢？

你可能也曾听闻过C语言的这三个变种（variation）。在你做出选择之前，需要先了解一下它们的区别。

## 2. C

我们从C语言开始讲起，因为它是三者中最老的、使用范围最广的语言。Dennis Ritchie在1972年创造了C语言并在1978年公布。Ritchie设计C的初衷是用于开发新版本的Unix。

在那之前，Unix使用的是汇编语言（assembly language），它是计算机可读取的最**低级**的编程。C语言的诞生彻底改变（revolutionize）了编程和操作系统。其余的，正如他们所说，是一段历史了。（译者注：就是夸C语言很屌就是了。）

译者注：语言的低级或者高级，并不是说语言的厉害程度。低级指的是更加接近于底层，计算机执行起来更快但是不利于人类理解，高级则相反。

C也是一门低级的编程语言，它的效率和汇编接近。它提供了基本级（base-level）的访问内存方式，对运行时支持的要求非常小。

尽管它已经诞生了40多年，但是它依然得到广泛的使用（译者注：看TIOBE就知道了，2019年12月排名第二，仅次于Java）。开发人员仍然使用它在操作系统、内核级软件开发、硬件驱动和需要与旧代码一同工作的应用程序上。

许多老牌的学校会建议C语言作为首选语言，因为许多后来的语言借鉴了C。由于C的年龄原因，使用C也可能带来一些安全性的提升。因为使用C的用户比较少，因此它比较不容易成为黑客的目标。

## 3. C++

C++是作为C的扩展来开发的。它是由丹麦的哲学博士（Ph.D.）Bjarne Stroustrup开发的。他的目标是增强C语言并在不牺牲速度和效率的前提下为其增加面向对象（object-oriented）的能力。

C++被认为是一种中级的语言，因为它基于低级的C语言所创建并拥有一些高级的能力。

自从1985年其发布以来，它已成为了另一个高产的编程语言。在开发操作系统时它会和C一同协作，但是在一些high-profile服务器和PC软件上也能看到它的身影。

译者注：high-profile，可以理解为高调的意思，例如游戏PC领域的雷蛇、外星人系列。

如果你的C语言功底扎实，那么你理解C++也是易如反掌；不过，如果你想立刻体验面向对象编程的话，也可以将C++作为你的第一门编程语言。（译者注：不是应该第一时间先找个对象吗？）

## 4. C#

C#是一门高级的面向对象的编程语言，同样也是作为C的扩展所创建的。它是在2002年，由微软的一个团队的领头人Anders Hejlsberg开发的。它是基于.NET框架的，但是它的核心依然是C语言。

C#将代码编译成字节码（byte-code）而不是机器码（0101的二进制）。这意味着它会在一台虚拟计算机上运行，这台虚拟机实时（on the fly）将字节码翻译成机器码。它在C语言的基础上添加了垃圾回收（garbage collection）、未初始化的变量检查（uninitialized variable checking）、边界检查（bound checking）和类型检查（type checking）这些特性。

译者注：翻译到这里的时候我就想到了Java以及JVM。

C#常见于内部或者企业应用而不是商业软件。可以在.NET框架中的客户端和服务器端开发中找到。

虽然C#是三门语言中技术上最复杂的，但是它的语法相对于C和C++来说更不容易出错，因此相对来说它的学习会更快点。

##  5. 主要的区别

虽然C和C++有许多的不同但是它们本质上是非常相似的编程语言。C#的话，换句话说它和Java会更相似。

### 5.1 C vs. C++

要完全理解C和C++的区别，你需要理解什么是面向对象。编程语言中的面向对象这个术语，最早起源于上个世纪50年代末或者60年代初，由麻省理工学院（MIT）提出。

面向对象编程（OOP）使用了一种叫做对象（object）的概念。一个对象是一个类（class）或者一个程序代码模板的实例。类可以由数据和代码过程（procedure，也叫做方法（method））组成。

C语言是不支持面向对象的，这也是它和C++的最大的区别。C是纯过程式（procedural）编程语言，而C++是既支持过程式又支持面向对象的混合编程语言。

以下是C和C++的其他不同点。

- C++作为C的扩展，意味着它可以运行大部分C代码。但是反过来，C去运行C++的代码，就不行了。
- 作为一种面向对象的语言，C++支持多态（polymorphism）、封装（encapsulation）和继承（inheritance），但是C不支持。
- 在C中，数据和函数是“自由的实体”（free entities），这意味着你可以使用外部代码来操作它们。但是由于C++将数据和函数封装到一个单一的对象，就等同于对外部代码隐藏了，所以外部代码无法操作其数据和函数。
- C++使用名称空间（namespace）将代码组织为逻辑组并阻止了名称冲突（collision）。当你的代码基（code base）包含了多个库的时候会发生名称冲突。C不使用名称空间。
- C使用函数来实现输入和输出，而C++使用对象来实现输入和输出。
- C++支持引用变量（reference variable），而C不支持。引用变量是已存在变量的别名，可用于加速编码。
- C不支持错误和异常处理，但是C++支持。

### 5.2 C++ vs. C#

作为一款更现代的编程语言，C#被设计于与当前微软.NET框架共同工作，在客户端和web应用程序中均有涉猎。

C++是一门面向对象的语言，而C#被认为是一门面向组件（component）的编程语言。面向对象编程聚焦于将多个类结合起来链接为一个可执行的二进制程序，而面向组件编程使用可交换的代码模块（可独立运行）并且你不需要知道它们内部是如何工作的就可以使用它们。

以下是C++和C#的主要区别。

- C++将代码编译成机器码，而C#将代码编译成[CLR](https://en.wikipedia.org/wiki/Common_Language_Runtime)（一种.NET框架的虚拟机组件，它会被ASP.NET所解析）。
- C++要求用户手动处理内存，但是C#运行在虚拟机中，而虚拟机会自动处理内存。
- C#不使用指针（pointer），而C++可以在任何时候使用指针。
- 虽然C++的设计是用于Unix或类Unix的系统，但是它可以运行在任何的平台上。C#虽然已标准化，但是基本上只在Windows的环境下运行。
- C++可以创建独立（stand-alone）和控制台（console）程序。C#可以创建控制台，Windows，ASP.NET和移动（mobile）程序，但不能创建独立程序。

### 5.3 C vs. C#

虽然C和C#在技术上相互有所关联，但是它们几乎是完全不同的语言，因此它们之间有更多的不同之处。有C语言功底的同学在学习C#时会比较简单，因为有些语法是相似的；不过，即使你没有C语言基础一样可以轻松学习C#，因为它的语法非常简单（译者注：原文是forgiving，宽容）。

 

## 6. 如何选择自己的第一门编程语言？

现在，你已经清楚地了解了这三门语言的区别，那么该如何选择呢？

### 菜鸟程序猿

如果你此前从未接触过编程，那么许多计算机科学专家会建议你首选C语言。不仅仅是因为它相对于它的后继者拥有更少的选项（译者注：这里指的应该是语言特性，例如装饰器、垃圾回收等），而且许多语言的语法和概念都是借鉴C的。简而言之，当你学了C之后你再学习其他的任何语言都是易如反掌。

### 中级程序猿

如果你此前已经有过编程经验的话，那么你可以尝试C++。如今面向对象编程会比过程式编程更为常见，如果你已经有了一些OOP经验的话，那么你学习C++也会更快。

### 高级程序猿

如果你已经具备多种编程语言的开发经验的话，那么你的选择取决于你希望在新的编程经历当中得到什么。

一些年轻的开发人员选择学习C语言来学习编码的基础。经验丰富的前辈们往往看不起年轻的一代，因为他们不尊重自己的根（译者注：可能C语言代表了编程语言的根、基础，这里应该也是要强调重视基础的意思），因此具备C语言的知识可以作为新工作中的街头信誉（street cred）。（译者注：街头信誉可以理解为在某个领域受到某些人的敬仰之类的，例如乔丹之于篮球，不过街头可能更加像是周围所发生的事情）

C++在工作环境下有广泛的应用，因此具备C++开发能力可以带来许多工作机会。如果你已经有OOP的经验，并且希望以最小的学习代价尝试一门新的OOP语言，那么C++是个不错的选择。

如果你希望在微软.NET网站开发环境下工作的话，那么C#就是最好的选择。虽然它的使用情况没有前两者来得广泛，但是它依然有一席之地。

 

## 总结

了解它们的区别有助于你做出自己的选择。**无论哪种语言都有其优点和缺点，无论学习哪种语言都不会浪费时间！（译者注：犹豫不决才是）**现在，是时候做决定了。

## 参考

> [原文地址](https://www.cnblogs.com/alongdidi/p/c_cPlusPlus_cSharp_diff.html)
>
> 