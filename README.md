# Sistemas-Operacionais

Os três códigos presentes nesta pasta correspondem ao Trabalho I da disciplina de Sistemas Operacionais, desenvolvido pelos alunos João Felipe e Maykon Jordson. Os experimentos foram elaborados para investigar a hipótese de que a ordem de criação dos processos filhos poderia influenciar sua ordem de execução e término e, consequentemente, a ordem em que seriam recebidos pelo processo pai por meio de wait().

Os experimentos utilizam fork(), wait(), waitpid(), PIDs e códigos de retorno para observar o comportamento dos processos. Entretanto, a análise deve considerar que a ordem observada também é influenciada pela própria construção do programa e pelo escalonamento realizado pelo sistema operacional. Após um fork(), pai e filho tornam-se processos concorrentes, e não há garantia de que serão executados ou terminarão na ordem em que foram criados.

Dessa forma, os experimentos servem como base para discutir as diferenças entre ordem de criação, execução, término e coleta dos processos, bem como o papel dos mecanismos de sincronização. A investigação mais adequada exige também observar o comportamento dos processos sem wait() ou waitpid(), reduzindo a influência da sincronização explicitamente definida pelo próprio código.
