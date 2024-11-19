#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

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
    vector<Professor> professores_;

public:
    void adicionarLivro();
    void listarLivros();
    void adicionarUsuario();
    void listarUsuarios();
    void emprestarLivro();
    void devolverLivro();
    void menu();
};

class Menu{
    private:
        Biblioteca biblioteca_;
    public:
        Menu(Biblioteca &biblioteca);
        void limparTela();
        void principal();
        bool obterResposta();
};

int main() {
    setlocale(LC_ALL, "portuguese");
	ItemBiblioteca item(1, "Gato Maroto", 2000);
    Livro livro(2, "Babum 2", 2005, "Raul", "Comédia");
    Usuario usuario(1, "Lucas", 10);
    Biblioteca biblioteca;
    Menu menu(biblioteca);

	item.exibirDetalhes();
    livro.exibirDetalhes();

    cout << usuario.podeEmprestar() << endl;
    cout << usuario.getId() << endl;
    usuario.realizarEmprestimo();
    usuario.exibirUsuario();
    usuario.realizarDevolucao();
    usuario.exibirUsuario();

    menu.limparTela();
    biblioteca.menu();

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
	cout << "Emprestado: " << (emprestado_ ? "Sim" : "Não") << endl;
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
Livro::Livro(int id, string titulo, int ano, string autor, string genero):
ItemBiblioteca::ItemBiblioteca(id,titulo,ano), autor_(autor), genero_(genero){}

void Livro::exibirDetalhes(){
    cout << "---------------------------------------------------" << endl;
	cout << "Id: " << id_ << endl;
	cout << "Título: " << titulo_ << endl;
	cout << "Ano: " << ano_ << endl;
	cout << "Emprestado: " << (emprestado_ ? "Sim" : "Não") << endl;
    cout << "Autor: " << autor_ << endl;
    cout << "Gênero: " << genero_ << endl;
	cout << "---------------------------------------------------" << endl;
}

/*--------------------------------------------------
	1.3 Usuário
--------------------------------------------------*/
Usuario::Usuario(int id, string nome, int limiteEmprestimos):
id_(id), nome_(nome), limiteEmprestimos_(limiteEmprestimos), emprestimosAtuais_(0){}

int Usuario::getId(){
    return id_;
}

void Usuario::exibirUsuario(){
    cout << "---------------------------------------------------" << endl;
	cout << "Id: " << id_ << endl;
	cout << "Nome: " << nome_ << endl;
	cout << "Limite de empréstimos: " << limiteEmprestimos_ << endl;
	cout << "Emprestimos atuais: " << emprestimosAtuais_ << endl;
	cout << "---------------------------------------------------" << endl;
}

bool Usuario::podeEmprestar(){
    return emprestimosAtuais_ <= limiteEmprestimos_;
}

void Usuario::realizarEmprestimo(){
    if(podeEmprestar()){
        emprestimosAtuais_++;
    }
}

void Usuario::realizarDevolucao(){
    if(emprestimosAtuais_>0){
        emprestimosAtuais_--;
    }
}

/*--------------------------------------------------
	1.4 Aluno
--------------------------------------------------*/
Aluno::Aluno(int id, string nome):
Usuario(id, nome, 3){}

/*--------------------------------------------------
	1.5 Professor
--------------------------------------------------*/
Professor::Professor(int id, string nome):
Usuario(id, nome, 5){}

/*--------------------------------------------------
	1.6 Biblioteca
--------------------------------------------------*/
void Biblioteca::menu(){
    int opcao;
    cout << "---------------Sistema de Biblioteca--------------" << endl;
    cout << "1. Adicionar livro" << endl;
    cout << "2. Listar livros" << endl;
    cout << "3. Adicionar usuário" << endl;
    cout << "4. Listar usuários" << endl;
    cout << "5. Emprestar livro" << endl;
    cout << "6. Devolver livro" << endl;
    cout << "Escolha uma opção: ";
    cin >> opcao;
    cout << endl;
}

/*--------------------------------------------------
	1.7 Menu
--------------------------------------------------*/
Menu::Menu(Biblioteca &biblioteca):biblioteca_(biblioteca){}

void Menu::limparTela(){
    #ifdef _WIN32 || WIN32
        system("cls");
    #else __linux__
        system("clear");
    #endif
}

void Menu::principal(){
    limparTela();
    cout << "---------------Sistema de Biblioteca--------------" << endl;
    cout << "1. Adicionar livro" << endl;
    cout << "2. Listar livros" << endl;
    cout << "3. Adicionar usuário" << endl;
    cout << "4. Listar usuários" << endl;
    cout << "5. Emprestar livro" << endl;
    cout << "6. Devolver livro" << endl;
    cout << "Escolha uma opção: ";
}