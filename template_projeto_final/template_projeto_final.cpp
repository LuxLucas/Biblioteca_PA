#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ItemBiblioteca {
protected:
    int id_, ano_;
    string titulo_;
    bool emprestado_;

public:
	ItemBiblioteca(int id, string titulo, int ano);
	
    virtual void exibirDetalhes();
    int getId();
    bool isEmprestado();
    void emprestar();
    void devolver();
};

class Livro : public ItemBiblioteca {
protected:
	string autor_;
	string genero_;
	
public:
    Livro(int id, string titulo, int ano, string autor, string genero);      
    void exibirDetalhes() override;
};

class Usuario {
protected:
    int id_, limiteEmprestimos_, emprestimosAtuais_;
    string nome_;

public:
    Usuario(int id, string nome, int limiteEmprestimos);
        
    virtual void exibirUsuario();

    bool podeEmprestar();
    void realizarEmprestimo();
    void realizarDevolucao();
    int getId();
};

class Aluno : public Usuario {
public:
    Aluno(int id, string nome);
};

class Professor : public Usuario {
public:
    Professor(int id, string nome);
};

class Biblioteca {
    vector<Livro> livros_;
    vector<Aluno> alunos_;
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

int main() {
	ItemBiblioteca item(1, "Gato Maroto", 2000);
	item.exibirDetalhes();
    return 0;
}

/*--------------------------------------------------
Declaração de funções
--------------------------------------------------*/

/*--------------------------------------------------
	1.1 ItemBibioteca
--------------------------------------------------*/
ItemBiblioteca::ItemBiblioteca(int id, string titulo, int ano):
	id_(id), titulo_(titulo), ano_(ano), emprestado_(false){}
		
void  ItemBiblioteca::exibirDetalhes(){
	cout << "---------------------------------------------------" << endl;
	cout << "Id: " << id_ << endl;
	cout << "Título: " << titulo_ << endl;
	cout << "Ano: " << ano_ << endl;
	cout << "Emprestado: " << emprestado_ << endl;
	cout << "---------------------------------------------------" << endl;
}
		
int ItemBiblioteca::getId(){
	return id_;
}
		
bool ItemBiblioteca::isEmprestado(){
	return emprestado_;
}
		
void ItemBiblioteca::emprestar(){
	emprestado_ = true;
}
		
void ItemBiblioteca::devolver(){
	emprestado_ = false;
}
/*--------------------------------------------------
	1.2 Livro
--------------------------------------------------*/
