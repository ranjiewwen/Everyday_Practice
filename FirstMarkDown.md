## 学习MarkDownPad

突然兴趣来了，在博客园里面也有Markdown的格式，昨天晚上安装了MarkDownPad pro这个是免费的，但是有些功能不支持。本来想破解的，百度了很多方法感觉不靠谱，今天早上来突然激活成功了。于是开始学习一下。

首先开始搭建环境：[Markdown](http://www.markdownpad.com/)官方网站，可以下载免费版的；然后在参考：[MarkdownPad 2 Pro 注册码](http://blog.csdn.net/xiaohei5188/article/details/43964451) 将邮箱和密匙输入即可。

先根据MarkdownPad帮助文档：[Github风格Markdown语法指南学习](https://help.github.com/categories/writing-on-github/)。但是有的语法貌似不能再MarkDown上用，注意细节。注意看看帮助文档。

# the largest heading
## the second heading
### three
#### four
##### five
###### the smallest heading

## Styling Text
**This is bold text** __This is bold text__
 
*this is italicized*  _this is italicized_

~~ this was mistaken text ~~

**_this is extremely important_**

## Quoting（引用） text

>you can quoting text with a>

## Quoting code

Use `git status` to list all new or modified files that haven't yet been commited.

```git status （~~key）
git add
git commmit
```

## Links
this site was built usingk[Github Pages](https://pages.github.com/).

##[Section Links](https://pages.github.com/)  

## Relative links
[Contribution guidelines for this project](docs/CONTRIBUTION.md)

# section one
see [section one](#section-one)
## Lists

* George Wahinton(有空格)
* John Adams
* Thomas Jefferson

1. George Wahinton(有空格)
2. John Adams
3. Thomas Jefferson

1. Make my changes
  1. Fix bug
  2. Improve formatting
  * Make the headings bigger
2. Push my commits to GitHub
3. Open a pull request
  * Describe my changes
  * Mention all the members of my team
    * Ask for feedback

## Task lists

-  [x] finish my changes
-  [ ] Push my commits to github
-  [ ] Open a pull request

@github/support : shipit :

## Create a table

| First Header | Second Header |
| ------------ | ------------- |
| Content Cell | Content Cell  |

| First Header  | Second Header |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |


First Header  | Second Header
------------- | -------------
Content Cell  | Content Cell
Content Cell  | Content Cell

## Headers
this is an h1
=============

> ## This is a header.
> 
> 1.   This is the first list item.
> 2.   This is the second list item.
> 
> Here's some example code:
> 
>     return shell_exec("echo $input | $markdown_script");


## Header1
## <em> single assistant <em>


```ruby
require 'redcarpet'
markdown = Redcarpet.new("Hello World!")
puts markdown.to_html
```
<pre>
<code>
class A
{
 public:
	void fun(){}
};

#include <iostream>
using namespace std;

 int main()
 {
	cout << sizeof(A) << endl; 
	return 0;
 }
</code>
</pre>

