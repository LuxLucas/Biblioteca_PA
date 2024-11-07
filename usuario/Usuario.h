#ifndef USUARIO_H
#define USUARIO_H
class Usuario {
protected:
    int id, limiteEmprestimos, emprestimosAtuais;
    string nome;

public:
    Usuario(int id, string nome, int limiteEmprestimos);
        
    virtual void exibirUsuario();

    bool podeEmprestar();
    void realizarEmprestimo();
    void realizarDevolucao();
    int getId();
};
#endif // USUARIO_H

#ifndef ALUNO_H
#define
class Aluno : public Usuario {
	public:
	    Aluno(int id, string nome);
};
#endif // ALUNO_H

#ifndef PROFESSOR_H
#define PROFESSOR_H
class Professor : public Usuario {
	public:
	    Professor(int id, string nome);
};
#endif // PROFESSOR_H 
