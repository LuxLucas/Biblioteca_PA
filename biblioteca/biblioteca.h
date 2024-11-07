#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <vector>

class Biblioteca {
    vector<Livro> livros;
    vector<Aluno> alunos;
    vector<Professor> professores;

public:
    void adicionarLivro();
    void listarLivros();
    void adicionarUsuario();
    void listarUsuarios();
    void emprestarLivro();
    void devolverLivro();
    void menu();
};
#endif // BIBLIOTECA_H
