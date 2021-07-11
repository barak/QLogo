
//===-- qlogo/library.cpp - Library text implementation -------*- C++ -*-===//
//
// This file is part of QLogo.
//
// QLogo is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// QLogo is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with QLogo.  If not, see <http://www.gnu.org/licenses/>.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the QLogo library text, which
/// provides standard supporting functions to the QLogo language.
///
//===----------------------------------------------------------------------===//

#include "library.h"

QString libraryStr =
    "to ` :backq.list [:backq.depth 0]\n"
    "if emptyp :backq.list [op []]\n"
    "if equalp first :backq.list \"` ~\n"
    "   [op fput \"`\n"
    "            fput  (` first bf :backq.list :backq.depth+1)\n"
    "                  (` bf bf :backq.list :backq.depth)]\n"
    "if and wordp first :backq.list equalp first first :backq.list \", ~\n"
    "   [op backq.unquote (bf first :backq.list) (bf :backq.list) "
    ":backq.depth]\n"
    "if and wordp first :backq.list memberp first first :backq.list [\" :] ~\n"
    "   [op backq.word (first first :backq.list) (bf first :backq.list)\n"
    "                  (bf :backq.list) :backq.depth]\n"
    "if wordp first :backq.list ~\n"
    "   [op fput first :backq.list (` bf :backq.list :backq.depth)]\n"
    "op fput (` first :backq.list :backq.depth) (` bf :backq.list "
    ":backq.depth)\n"
    "end\n"
    "to backq.word :backq.symbol :backq.word :backq.rest :backq.depth\n"
    "if emptyp :backq.word ~\n"
    "   [output fput :backq.symbol (` :backq.rest :backq.depth)]\n"
    "if not equalp first :backq.word \", ~\n"
    "   [output fput (word :backq.symbol :backq.word)\n"
    "                (` :backq.rest :backq.depth)]\n"
    "localmake \"result backq.unquote (bf :backq.word) :backq.rest "
    ":backq.depth\n"
    "if wordp :result [output word :backq.symbol :result]\n"
    "output fput (word :backq.symbol first :result) bf :result\n"
    "end\n"
    "to backq.unquote :unquote.symbol :unquote.rest :unquote.depth\n"
    "localmake \"unquote.splicing \"false\n"
    "if not emptyp :unquote.symbol [\n"
    "   if equalp first :unquote.symbol \"@ [\n"
    "      make \"unquote.splicing \"true\n"
    "      make \"unquote.symbol butfirst :unquote.symbol\n"
    "]]\n"
    "if :unquote.depth=0 [\n"
    "  if emptyp :unquote.symbol\n"
    "     [output backq.combine run first :unquote.rest\n"
    "                           (` bf :unquote.rest :unquote.depth)]\n"
    "  output backq.combine run :unquote.symbol (` :unquote.rest "
    ":unquote.depth)\n"
    "]\n"
    "if emptyp :unquote.symbol ~\n"
    "   [output fput (ifelse :unquote.splicing [\",@] [\",])\n"
    "                fput (` first :unquote.rest :unquote.depth-1)\n"
    "                     (` bf :unquote.rest :unquote.depth)]\n"
    "if backq.all.commas :unquote.symbol ~\n"
    "   [output fput (ifelse :unquote.splicing [\",@] [\",])\n"
    "                fput (` (list :unquote.symbol first :unquote.rest)\n"
    "                        :unquote.depth-1)\n"
    "                     (` bf :unquote.rest :unquote.depth)]\n"
    "output fput (ifelse :unquote.splicing [\",@] [\",]) ~\n"
    "            fput (` (list :unquote.symbol) :unquote.depth-1) ~\n"
    "                 (` :unquote.rest :unquote.depth)\n"
    "end\n"
    "to backq.combine :this :those\n"
    "output ifelse :unquote.splicing [se :this :those] [fput :this :those]\n"
    "end\n"
    "to backq.all.commas :word\n"
    "if emptyp :word [output \"true]\n"
    "if equalp first :word \", ~\n"
    "   [if emptyp butfirst :word [output \"true]\n"
    "    if equalp first butfirst :word \"@ [output backq.all.commas bf bf "
    ":word]\n"
    "    output backq.all.commas butfirst :word]\n"
    "output \"false\n"
    "end\n"
    "\n"
    "to #\n"
    "if not namep \"template.number [op repcount]\n"
    "op :template.number\n"
    "end\n"
    "\n"
    "to backslashedp :char\n"
    "op vbarredp :char\n"
    "end\n"
    "\n"
    "to backslashed? :char\n"
    "op vbarredp :char\n"
    "end\n"
    "\n"
    "to buryall\n"
    "end\n"
    "\n"
    "to buryname :names\n"
    "end\n"
    "\n"
    "to cascade :cascade.limit [:cascade.inputs] 3\n"
    "if numberp :cascade.limit ~\n"
    "   [if lessp :cascade.limit 0 ~\n"
    "       [(throw \"error (se [cascade doesn't like] :cascade.limit [as "
    "input]))] ~\n"
    "    make \"cascade.limit `[greaterp :template.number ,[int "
    ":cascade.limit]]]\n"
    "local [cascade.templates template.vars cascade.final]\n"
    "make \"cascade.templates []\n"
    "make \"template.vars []\n"
    "make \"cascade.final [?1]\n"
    "cascade.setup :cascade.inputs\n"
    "op cascade1 1 :template.vars\n"
    "end\n"
    "to cascade.setup :inputs\n"
    "if emptyp :inputs [stop]\n"
    "if emptyp bf :inputs [make \"cascade.final first :inputs stop]\n"
    "make \"cascade.templates lput first :inputs :cascade.templates\n"
    "make \"template.vars lput first bf :inputs :template.vars\n"
    "cascade.setup bf bf :inputs\n"
    "end\n"
    "to cascade1 :template.number :template.vars\n"
    "if apply :cascade.limit :template.vars [op apply :cascade.final "
    ":template.vars]\n"
    "op cascade1 (:template.number+1) (cascade.eval :cascade.templates)\n"
    "end\n"
    "to cascade.eval :cascade.templates\n"
    "if emptyp :cascade.templates [op []]\n"
    "op fput (apply first :cascade.templates :template.vars) ~\n"
    "        (cascade.eval bf :cascade.templates)\n"
    "end\n"
    "\n"
    "to cascade.2 [:cascade2.inputs] 5\n"
    "op apply \"cascade :cascade2.inputs\n"
    "end\n"
    "\n"
    ".macro case :case.value :case.clauses [:caseignoredp \"true]\n"
    "catch \"case.error [output case.helper :case.value :case.clauses]\n"
    "(throw \"error [Empty CASE clause])\n"
    "end\n"
    "to case.helper :case.value :case.clauses\n"
    "if emptyp :case.clauses [output []]\n"
    "if emptyp first :case.clauses [throw \"case.error]\n"
    "if or equalp first first :case.clauses \"else ~\n"
    "      memberp :case.value first first :case.clauses ~\n"
    "   [output butfirst first :case.clauses]\n"
    "output case.helper :case.value butfirst :case.clauses\n"
    "end\n"
    "\n"
    ";to closeall\n"
    ";foreach allopen [close ?]\n"
    ";end\n"
    "\n"
    "to combine :this :those\n"
    "if wordp :those [output word :this :those]\n"
    "output fput :this :those\n"
    "end\n"
    "\n"
    ".macro cond :cond.clauses\n"
    "localmake \"cond.result cond.helper :cond.clauses\n"
    "if equalp first :cond.result \"error [(throw \"error last :cond.result)]\n"
    "output last :cond.result\n"
    "end\n"
    "to cond.helper :cond.clauses\n"
    "if emptyp :cond.clauses [output [[] []]]\n"
    "if emptyp first :cond.clauses [output [error [Empty COND clause]]]\n"
    "if equalp first first :cond.clauses \"else ~\n"
    "   [output list [] butfirst first :cond.clauses]\n"
    "ignore error\n"
    "catch \"error [localmake \"cond.result run first first :cond.clauses]\n"
    "localmake \"cond.error error\n"
    "if not emptyp :cond.error [output list \"error item 2 :cond.error]\n"
    "if not memberp :cond.result [true false] ~\n"
    "   [output list \"error fput :cond.result [not TRUE or FALSE]]\n"
    "if :cond.result [output list [] butfirst first :cond.clauses]\n"
    "output cond.helper butfirst :cond.clauses\n"
    "end\n"
    "\n"
    "to crossmap :cm.template [:cm.lists] 2\n"
    "if emptyp bf :cm.lists [op cm1 first :cm.lists 1 []]\n"
    "op cm1 :cm.lists 1 []\n"
    "end\n"
    "to cm1 :cm.lists :cm.level :template.vars\n"
    "if emptyp :cm.lists [op (list apply :cm.template :template.vars)]\n"
    "op cm2 first :cm.lists\n"
    "end\n"
    "to cm2 :cm.thislist\n"
    "if emptyp :cm.thislist [op []]\n"
    "local :cm.level\n"
    "make :cm.level first :cm.thislist\n"
    "op se (cm1 bf :cm.lists :cm.level+1 lput first :cm.thislist "
    ":template.vars) ~\n"
    "      (cm2 bf :cm.thislist)\n"
    "end\n"
    "\n"
    "to dequeue :the.queue.name\n"
    "local \"result\n"
    "make \"result first thing :the.queue.name\n"
    "make :the.queue.name butfirst thing :the.queue.name\n"
    "output :result\n"
    "end\n"
    "\n"
    ".macro do.until :until.instr :until.cond\n"
    "op se :until.instr (list \"until :until.cond :until.instr)\n"
    "end\n"
    "\n"
    ".macro do.while :while.instr :while.cond\n"
    "op se :while.instr (list \"while :while.cond :while.instr)\n"
    "end\n"
    "\n"
    "to edall\n"
    "edit contents\n"
    "end\n"
    "\n"
    "to edn :names\n"
    "edit namelist :names\n"
    "end\n"
    "\n"
    "to edns\n"
    "edit names\n"
    "end\n"
    "\n"
    "to edpl :names\n"
    "edit pllist :names\n"
    "end\n"
    "\n"
    "to edpls\n"
    "edit plists\n"
    "end\n"
    "\n"
    "to edps\n"
    "edit procedures\n"
    "end\n"
    "\n"
    "to ern :names\n"
    "erase namelist :names\n"
    "end\n"
    "\n"
    "to erpl :names\n"
    "erase pllist :names\n"
    "end\n"
    "\n"
    "to filep :filename\n"
    "ignore error\n"
    "catch \"error [openread :filename close :filename]\n"
    "output emptyp error\n"
    "end\n"
    "\n"
    "to file? :filename\n"
    "ignore error\n"
    "catch \"error [openread :filename close :filename]\n"
    "output emptyp error\n"
    "end\n"
    "\n"
    "to filter :filter.template :template.list [:template.number 1] ~\n"
    "          [:template.lists (list :template.list)]\n"
    "if emptyp :template.list [op :template.list]\n"
    "if apply :filter.template (list first :template.list) ~\n"
    "   [op combine (first :template.list) ~\n"
    "               (filter :filter.template bf :template.list "
    ":template.number+1)]\n"
    "op (filter :filter.template bf :template.list :template.number+1)\n"
    "end\n"
    "to ?rest [:which 1]\n"
    "output bf item :which :template.lists\n"
    "end\n"
    "\n"
    "to find :find.template :template.list [:template.number 1] ~\n"
    "        [:template.lists (list :template.list)]\n"
    "if emptyp :template.list [op []]\n"
    "if apply :find.template (list first :template.list) [op first "
    ":template.list]\n"
    "op (find :find.template bf :template.list :template.number+1)\n"
    "end\n"
    "to ?rest [:which 1]\n"
    "output bf item :which :template.lists\n"
    "end\n"
    "\n"
    ".macro for :for.values :for.instr ~\n"
    "   [:for.var first :for.values] ~\n"
    "   [:for.initial run first bf :for.values] ~\n"
    "   [:for.final run first bf bf :for.values] ~\n"
    "   [:for.step forstep] ~\n"
    "   [:for.tester (ifelse :for.step < 0 ~\n"
    "                        [[:for.initial < :for.final]] ~\n"
    "                        [[:for.initial > :for.final]])]\n"
    "local :for.var\n"
    "catch \"for.catchtag [op for.done runresult [forloop :for.initial]]\n"
    "op []\n"
    "end\n"
    "to forloop :for.initial\n"
    "make :for.var :for.initial\n"
    "if run :for.tester [throw \"for.catchtag]\n"
    "run :for.instr\n"
    ".maybeoutput forloop (:for.initial + :for.step)\n"
    "end\n"
    "to for.done :for.result\n"
    "if emptyp :for.result [op [stop]]\n"
    "op (list \"output \"first (list first :for.result))\n"
    "end\n"
    "to forstep\n"
    "if equalp count :for.values 4 [op run last :for.values]\n"
    "op ifelse :for.initial > :for.final [-1] [1]\n"
    "end\n"
    "\n"
    ".macro foreach [:foreach.inputs] 2\n"
    "catch \"foreach.catchtag ~\n"
    "      [op foreach.done runresult ~\n"
    "	    [foreach1 bl :foreach.inputs last :foreach.inputs 1]]\n"
    "op []\n"
    "end\n"
    "to foreach1 :template.lists :foreach.template :template.number\n"
    "if emptyp first :template.lists [throw \"foreach.catchtag]\n"
    "apply :foreach.template firsts :template.lists\n"
    ".maybeoutput foreach1 bfs :template.lists :foreach.template "
    ":template.number+1\n"
    "end\n"
    "to foreach.done :foreach.result\n"
    "if emptyp :foreach.result [op [stop]]\n"
    "op (list \"output \"first (list first :foreach.result))\n"
    "end\n"
    "to ?rest [:which 1]\n"
    "output bf item :which :template.lists\n"
    "end\n"
    "\n"
    "to gensym\n"
    "if not namep \"gensym.number [make \"gensym.number 0]\n"
    "make \"gensym.number :gensym.number + 1\n"
    "output word \"g :gensym.number\n"
    "end\n"
    "\n"
    "to ignore :stuff\n"
    "end\n"
    "\n"
    "to invoke :invoked.function [:invoke.inputs] 2\n"
    ".maybeoutput apply :invoked.function :invoke.inputs\n"
    "end\n"
    "\n"
    "to iseq :a :b\n"
    "if not (:a > :b) [output iseq1 :a :b]\n"
    "output map [[x] -1 * :x] iseq1 (-1 * :a) (-1 * :b)\n"
    "end\n"
    "to iseq1 :a :b\n"
    "if :a > :b [output []]\n"
    "output fput :a iseq1 :a + 1 :b\n"
    "end\n"
    "\n"
    ".macro localmake :name :value\n"
    "output (list \"local (word \"\" :name) \"apply \"\"make (list :name "
    ":value))\n"
    "end\n"
    "\n"
    "to macroexpand :expr\n"
    "local [name inputlist macro.result]\n"
    "make \"name first :expr\n"
    "make \"inputlist bf :expr\n"
    "if not macrop :name [(throw \"error (se :name [is not a macro.]))]\n"
    "define \"%%%$%macro.procedure text :name\n"
    "make \"macro.result run fput \"%%%$%macro.procedure :inputlist\n"
    "erase \"%%%$%macro.procedure\n"
    "op :macro.result\n"
    "end\n"
    "\n"
    "to map :map.template [:template.lists] 2\n"
    "op map1 :template.lists 1\n"
    "end\n"
    "to map1 :template.lists :template.number\n"
    "if emptyp first :template.lists [output first :template.lists]\n"
    "output combine (apply :map.template firsts :template.lists) ~\n"
    "               (map1 bfs :template.lists :template.number+1)\n"
    "end\n"
    "to ?rest [:which 1]\n"
    "output bf item :which :template.lists\n"
    "end\n"
    "\n"
    "to map.se :map.se.template [:template.lists] 2\n"
    "op map.se1 :template.lists 1\n"
    "end\n"
    "to map.se1 :template.lists :template.number\n"
    "if emptyp first :template.lists [output []]\n"
    "output sentence (apply :map.se.template firsts :template.lists) ~\n"
    "                (map.se1 bfs :template.lists :template.number+1)\n"
    "end\n"
    "to ?rest [:which 1]\n"
    "output bf item :which :template.lists\n"
    "end\n"
    "\n"
    "to mdarray :sizes [:origin 1]\n"
    "local \"array\n"
    "make \"array (array first :sizes :origin)\n"
    "if not emptyp bf :sizes ~\n"
    "   [for [i :origin [:origin + (first :sizes) - 1]] ~\n"
    "        [setitem :i :array (mdarray bf :sizes :origin)]]\n"
    "output :array\n"
    "end\n"
    "\n"
    "to mditem :index :array\n"
    "if emptyp :index [op :array]\n"
    "op mditem bf :index item first :index :array\n"
    "end\n"
    "\n"
    "to mdsetitem :index :array :val\n"
    "setitem last :index (mditem bl :index :array) :val\n"
    "end\n"
    "\n"
    "to name :name.value.input :name.variable.input\n"
    "make :name.variable.input :name.value.input\n"
    "end\n"
    "\n"
    "to namelist :names\n"
    "if wordp :names [output list [] (list :names)]\n"
    "output list [] :names\n"
    "end\n"
    "\n"
    "to pen\n"
    "op (list (ifelse pendownp [\"pendown] [\"penup]) ~\n"
    "         penmode pensize pencolor penpattern)\n"
    "end\n"
    "\n"
    "to pick :list\n"
    "output item (1+random count :list) :list\n"
    "end\n"
    "\n"
    "to pllist :names\n"
    "if wordp :names [output (list [] [] (list :names))]\n"
    "output (list [] [] :names)\n"
    "end\n"
    "\n"
    "to poall\n"
    "po contents\n"
    "end\n"
    "\n"
    "to pon :names\n"
    "ignore error\n"
    "catch \"error [po namelist :names]\n"
    "local \"err\n"
    "make \"err error\n"
    "if not emptyp :err [(throw \"error first bf :err)]\n"
    "end\n"
    "\n"
    "to pons\n"
    "po names\n"
    "end\n"
    "\n"
    "to pop :the.stack.name\n"
    "local \"result\n"
    "make \"result first thing :the.stack.name\n"
    "make :the.stack.name butfirst thing :the.stack.name\n"
    "output :result\n"
    "end\n"
    "\n"
    "to popl :names\n"
    "ignore error\n"
    "catch \"error [po pllist :names]\n"
    "local \"err\n"
    "make \"err error\n"
    "if not emptyp :err [(throw \"error first bf :err)]\n"
    "end\n"
    "\n"
    "to popls\n"
    "po plists\n"
    "end\n"
    "\n"
    "to pops\n"
    "po procedures\n"
    "end\n"
    "\n"
    "to pots\n"
    "pot procedures\n"
    "end\n"
    "\n"
    "to push :the.stack.name :the.item.value\n"
    "make :the.stack.name fput :the.item.value thing :the.stack.name\n"
    "end\n"
    "\n"
    "to ?rest [:which 1]\n"
    "output bf item :which :template.lists\n"
    "end\n"
    "\n"
    "to queue :the.queue.name :the.item.value\n"
    "make :the.queue.name lput :the.item.value thing :the.queue.name\n"
    "end\n"
    "\n"
    "to quoted :stuff\n"
    "if wordp :stuff [op word \"\" :stuff]\n"
    "op :stuff\n"
    "end\n"
    "\n"
    "to reduce :reduce.function :reduce.list\n"
    "if emptyp bf :reduce.list [op first :reduce.list]\n"
    "op apply :reduce.function (list (first :reduce.list) ~\n"
    "                                (reduce :reduce.function bf "
    ":reduce.list))\n"
    "end\n"
    "\n"
    "to remdup :list\n"
    "output filter [not memberp ? ?rest] :list\n"
    "end\n"
    "\n"
    "to remove :thing :list\n"
    "output filter [not equalp ? :thing] :list\n"
    "end\n"
    "\n"
    "to reverse :in [:out ifelse listp :in [[]] [\"]]\n"
    "if emptyp :in [output :out]\n"
    "output (reverse bf :in combine first :in :out)\n"
    "end\n"
    "\n"
    "to rseq :a :b :n\n"
    "output map [[x] :a + :x * (:b - :a) / (:n - 1)] iseq 0 :n - 1\n"
    "end\n"
    "\n"
    "to savel :cont :file [:oldwr writer]\n"
    "openwrite :file\n"
    "setwrite :file\n"
    "po :cont\n"
    "setwrite :oldwr\n"
    "close :file\n"
    "end\n"
    "\n"
    "to setpen :pen_data\n"
    "ifelse equalp first bf :pen_data \"reverse ~\n"
    "       [penreverse] ~\n"
    "       [ifelse equalp first bf :pen_data \"erase ~\n"
    "               [penerase] ~\n"
    "               [penpaint]]\n"
    "ifelse equalp first :pen_data \"penup [penup] [pendown]\n"
    "setpensize first bf bf :pen_data\n"
    "setpencolor first bf bf bf :pen_data\n"
    "setpenpattern first bf bf bf bf :pen_data\n"
    "end\n"
    "\n"
    "to transfer :transfer.limit :transfer.template :transfer.init\n"
    "output cascade.2 (ifelse emptyp :transfer.limit ~\n"
    "                         [[emptyp ?2]] ~\n"
    "                         [list \"transfer.end.test :transfer.limit]) ~\n"
    "                 :transfer.template [] [butfirst ?2] :transfer.init\n"
    "end\n"
    "\n"
    "to transfer.end.test :the.condition.expression\n"
    "if emptyp ?2 [output \"true]\n"
    "output run :the.condition.expression\n"
    "end\n"
    "to ?in\n"
    "output first ?2\n"
    "end\n"
    "to ?out\n"
    "output ?1\n"
    "end\n"
    "\n"
    "to unburyall\n"
    "unbury buried\n"
    "end\n"
    "to unburyname :names\n"
    "unbury namelist :names\n"
    "end\n"
    "\n"
    ".macro until :until.cond :until.instr\n"
    "if run :until.cond [op []]\n"
    "op se :until.instr (list \"until :until.cond :until.instr)\n"
    "end\n"
    "\n"
    ".macro while :while.cond :while.instr\n"
    "if not run :while.cond [op []]\n"
    "op se :while.instr (list \"while :while.cond :while.instr)\n"
    "end\n"
    "\n"
    "to xcor\n"
    "output first pos\n"
    "end\n"
    "\n"
    "to ycor\n"
    "output last pos\n"
    "end\n"
    "\n"
    "make \"caseignoredp \"true\n"
    "bury [[][caseignoredp][]]\n"
    "\n"
    "bury [` backq.word backq.unquote backq.combine backq.all.commas # "
    "backslashedp backslashed? contents buryall namelist\n"
    "        :names buryname cascade cascade.setup cascade1 cascade.eval "
    "cascade.2 case case.helper closeall combine cond\n"
    "        cond.helper crossmap cm1 cm2 dequeue do.until do.while edall edn "
    "edns edpl edpls edps emacs.debug ern erpl\n"
    "        filep file? filter ?rest find ?rest for forstep forloop for.done "
    "foreach foreach1 foreach.done ?rest ignore\n"
    "        invoke iseq iseq1 localmake macroexpand map map1 ?rest map.se "
    "map.se1 ?rest mdarray mditem mdsetitem name\n"
    "        namelist pen pick pllist poall pon pons pop popl popls pops pots "
    "push ?rest queue quoted reduce remdup remove\n"
    "        reverse rseq savel setpen transfer transfer.end.test ?in ?out "
    "unburyname until while xcor ycor gensym unburyall\n"
    "        [wr_elisp_code pw_elisp_code file_elisp_code trace_or_step "
    "gensym.number] []]\n";
