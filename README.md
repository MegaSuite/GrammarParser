<h1 align='center'>GrammarParser</h1>

> Course Design Of Programming -- Huazhong University of Science and Technology Sophomore

## 选题：基于高级语言源程序格式处理工具
在计算机科学中，抽象语法树（abstract syntax tree或者缩写为AST），是将源代码的语法结构的用树的形式表示，树上的每个结点都表示源程序代码中的一种语法成分。之所以说是“抽象”，是因为在抽象语法树中，忽略了源程序中语法成分的一些细节，突出了其主要语法特征。

抽象语法树(Abstract Syntax Tree ,AST)作为程序的一种中间表示形式,在程序分析等诸多领域有广泛的应用.利用抽象语法树可以方便地实现多种源程序处理工具,比如源程序浏览器、智能编辑器、语言翻译器等。

在《高级语言源程序格式处理工具》这个题目中，首先需要采用形式化的方式，使用巴克斯（BNF）范式定义高级语言的词法规则（字符组成单词的规则）、语法规则（单词组成语句、程序等的规则）。再利用形式语言自动机的的原理，对源程序的文件进行词法分析，识别出所有单词；使用编译技术中的递归下降语法分析法，分析源程序的语法结构，并生成抽象语法树,最后可由抽象语法树生成格式化的源程序

## 项目结构
基于[Fly-lovest](https://github.com/fly-lovest/HUST-CS-Comprehensive-Programming-Course)的项目进行修改，增加了对词法分析器具体报错（所在行，具体错误内容）的支持，使输出规范化，添加了语法分析的具体报错支持，提高了容错能力，优化了显示界面不完整的问题，使程序运行更稳定。

## 环境
本项目在`JetBrains CLion`环境中开发，请默认使用`CLion`打开项目，其他`IDE`请自行配置。
## 参考
《编译原理（第 3 版）》（王生原，董渊，张素琴，吕映芝等 [北京]清华大学出版社 ）

[杨茂林老师编译原理课程](https://space.bilibili.com/503076092/?spm_id_from=333.999.0.0)

[fly-lovest的编译原理仓库](https://github.com/fly-lovest/HUST-CS-Compilation-Principle)
