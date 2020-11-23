# Compilers-Principles
A repository for saving my own pl/0 language compiler

The pl/0 language is as follows, described in Backus-Naur form:

&lt;prog &gt      -> program&ltid&gt;&ltblock&gt
&ltblock&gt     -> [&ltcondecl&gt][&ltvardecl&gt][&ltproc&gt]&ltbody&gt
&ltcondecl&gt   -> const<const>{,<const>};
&ltconst&gt     -> <id>:=<integer>
&ltvardecl&gt   -> var<id>{,<id>};
&ltproc&gt      -> procedure<id>([<id>{,<id>}]);<block>{;<proc>}
&ltbody&gt      -> begin<statement>{;<statement>}end
&ltstatement&gt -> <id>:=<exp>
              |if<lexp>then<statement>[else<statement>]
              |while<lexp>do<statement>
              |call<id>([<exp>{,<exp>}])
              |<body>
              |read(<id>{,<id>})
              |write(<exp>{,<exp>})
&ltlexp&gt     -> <exp><lop><exp>|odd<exp>
&ltexp&gt      -> [+|-]<term>{<aop><term>}
&ltterm&gt     -> <factor>{<mop><factor>}
&ltfactor&gt   -> <id>|<integer>|(<exp>)
&ltlop&gt      -> =|<>|<|<=|>|>=
&ltaop&gt      -> +|-
&ltmop&gt      -> *|/
&ltid&gt       -> l{l|d}
&ltinteger&gt  -> d{d}
