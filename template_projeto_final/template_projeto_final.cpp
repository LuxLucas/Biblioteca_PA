#include <iostream>
#include <vector>
#include <string>

//Para usar função system
#include <stdlib.h>

#include <thread> //Para parar o programa temporariamente
#include <chrono> //Contagem de tempo


using namespace std;

const int segundosDeEspera = 2;

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
    int idLeitor_;
	
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

    int ultimoIdLivro = 0, ultimoIdProfessor = 0, ultimoIdAluno = 0;

protected:
    bool validarNome(string nome);
    bool validarCriacaoDeLivro(string nomeLivro, string nomeAutor, string genero, int anoPublicacao);
    bool alunoExiste(int idAluno);
    bool professorExiste(int idProfessor);
    bool livroExiste(int idLivro);
    int registrarIdLivro();
    int registrarIdProfessor();
    int registrarIdAluno();

public:
    void adicionarLivro();
    void listarLivros();
    void adicionarUsuario();
    void listarUsuarios();
    void emprestarLivro();
    void devolverLivro();
    //A função menu era do tipo void
    int menu();

    void limparTela();
};

int main() {
    setlocale(LC_ALL, "portuguese");
    Biblioteca biblioteca;
    int opcao;

    while(true){
        biblioteca.limparTela();
        opcao = biblioteca.menu();

        if(opcao == 0){
            break;
        }
        switch(opcao){
            case 1:
                biblioteca.limparTela();
                biblioteca.adicionarLivro();
                break;
            case 2:
                biblioteca.limparTela();
                biblioteca.listarLivros();
                break;
            default: 
                cout << "ERRO: Comando inválido\n";
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
                biblioteca.limparTela();
        }
    }

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
ItemBiblioteca::ItemBiblioteca(id,titulo,ano), autor_(autor), genero_(genero), idLeitor_(0){}

void Livro::exibirDetalhes(){
    cout << "---------------------------------------------------" << endl;
	cout << "Id: " << id_ << endl;
	cout << "Título: " << titulo_ << endl;
	cout << "Ano: " << ano_ << endl;
	cout << "Emprestado: " << (emprestado_ ? "Sim" : "Não") << endl;
    cout << "Autor: " << autor_ << endl;
    cout << "Gênero: " << genero_ << endl;
    cout << "Id do leitor: " << idLeitor_ << endl;
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
void Biblioteca::limparTela(){
    #ifdef _WIN32 || WIN32
        system("cls");
    #else __linux__
        system("clear");
    #endif
}
 
bool Biblioteca::validarNome(string nome){
    return nome.length() > 0;
}

bool Biblioteca::alunoExiste(int idAluno){
    for(Aluno aluno: alunos_){
        if(aluno.getId() == idAluno){
            return true;
        }
    }
    return false;
}

bool Biblioteca::professorExiste(int idProfessor){
    for(Professor professor: professores_){
        if(professor.getId() == idProfessor){
            return true;
        }
    }
    return false;
}

bool Biblioteca::livroExiste(int idLivro){
    for(Livro livro: livros_){
        if(livro.getId() == idLivro){
            return true;
        }
    }
    return false;
}

bool Biblioteca::validarCriacaoDeLivro(string nomeLivro, string nomeAutor, string genero, int anoPublicacao){
    return  (nomeLivro.length() > 0) && 
            (nomeAutor.length() > 0) && 
            (genero.length() > 0) && 
            (anoPublicacao > 0 && anoPublicacao <= 2024);
}

int Biblioteca::registrarIdLivro(){
    ultimoIdLivro++;
    return ultimoIdLivro;
}

int Biblioteca::registrarIdProfessor(){
    ultimoIdProfessor++;
    return ultimoIdProfessor;
}

int Biblioteca::registrarIdAluno(){
    ultimoIdAluno++;
    return ultimoIdAluno;
}

void Biblioteca::adicionarLivro(){
    string nomeLivro, nomeAutor, genero, resposta;
    int anoPublicacao;

    cout << "-----------------Adicionando Livro----------------" << endl;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nomeLivro);

    cout << "Autor: ";
    getline(cin, nomeAutor);

    cout << "Gênero: ";
    getline(cin, genero);

    cout << "Ano de publicação: ";
    cin >> anoPublicacao;       

    if(validarCriacaoDeLivro(nomeLivro, nomeAutor, genero, anoPublicacao) && !cin.fail()){
        livros_.emplace_back(registrarIdLivro(), nomeLivro, anoPublicacao, nomeAutor, genero);
        cout << "\nLivro adicionado" << endl;
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }else{
        cout << "\nERRO: Valor indevido inserido" << endl;
        cin.clear();
        cin.ignore();
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }
}

void Biblioteca::listarLivros(){
    if(livros_.size() == 0){
        cout << "\nNão há livros listados";
        cin.ignore();
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }else{
        cout << "-----------------Listagem de livros----------------" << endl;
        for(Livro livro: livros_){
            livro.exibirDetalhes();
        }
        cout << "\nPrescione ENTER para continuar...";
        cin.ignore();
        cin.get();
    }
}

int Biblioteca::menu(){
    int opcao;
    cout << "\n---------------Sistema de Biblioteca--------------" << endl;
    cout << "1. Adicionar livro" << endl;
    cout << "2. Listar livros" << endl;
    cout << "3. Adicionar usuário" << endl;
    cout << "4. Listar usuários" << endl;
    cout << "5. Emprestar livro" << endl;
    cout << "6. Devolver livro" << endl;
    cout << "0. Sair do programa" << endl;
    cout << "\nEscolha uma opção: ";
    cin >> opcao;
    
    return (7 > opcao) && (opcao > -1) ? opcao : -1;
}