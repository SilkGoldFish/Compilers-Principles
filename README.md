# Compilers-Principles
**A repository for saving my own pl/0 language compiler**

**Important Notification:**<br>
**Each line of the test file should end up with a blank character.(According to some unknown system errors)**<br>

## Pl/0 language
The pl/0 language is as follows, described in Backus-Naur form:

&lt;prog&gt;->program&lt;id&gt;;&lt;block&gt;<br>
&lt;block&gt;->[&lt;condecl&gt;][&lt;vardecl&gt;][&lt;proc&gt;]&lt;body&gt;<br>
&lt;condecl&gt;->const&lt;const&gt;{,&lt;const&gt;};<br>
&lt;const&gt;->&lt;id&gt;:=&lt;integer&gt;<br>
&lt;vardecl&gt;->var&lt;id&gt;{,&lt;id&gt;};<br>
&lt;proc&gt;->procedure&lt;id&gt;([&lt;id&gt;{,&lt;id&gt;}]);&lt;block&gt;{;&lt;proc&gt;}<br>
&lt;body&gt;->begin&lt;statement&gt;{;&lt;statement&gt;}end<br>
&lt;statement&gt;->&lt;id&gt;:=&lt;exp&gt;<br>
&emsp;&emsp;|if&lt;lexp&gt;then&lt;statement&gt;[else&lt;statement&gt;]<br>
&emsp;&emsp;|while&lt;lexp&gt;do&lt;statement&gt;<br>
&emsp;&emsp;|call&lt;id&gt;([&lt;exp&gt;{,&lt;exp&gt;}])<br>
&emsp;&emsp;|&lt;body&gt;<br>
&emsp;&emsp;|read(&lt;id&gt;{,&lt;id&gt;})<br>
&emsp;&emsp;|write(&lt;exp&gt;{,&lt;exp&gt;})<br>
&lt;lexp&gt;->&lt;exp&gt;&lt;lop&gt;&lt;exp&gt;|odd&lt;exp&gt;<br>
&lt;exp&gt;->[+|-]&lt;term&gt;{&lt;aop&gt;&lt;term&gt;}<br>
&lt;term&gt;->&lt;factor&gt;{&lt;mop&gt;&lt;factor&gt;}<br>
&lt;factor&gt;->&lt;id&gt;|&lt;integer&gt;|(&lt;exp&gt;)<br>
&lt;lop&gt;->=|&lt;&gt;|&lt;|&lt;=|&gt;|&gt;=<br>
&lt;aop&gt;->+|-<br>
&lt;mop&gt;->*|/<br>
&lt;id&gt;->l{l|d}<br>
&lt;integer&gt;->d{d}<br>
