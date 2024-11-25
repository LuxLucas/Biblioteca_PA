#include <iostream>
#include <vector>
#include <string>

#include <stdlib.h> //Para usar a função system
#include <thread> //Permite pausar o programa
#include <chrono> //Possui funções para contar a passagem do tempo

using namespace std;

const int segundosDeEspera = 2;

class ItemBiblioteca {
protected:
    int id_, ano_, idLeitor_;
    string titulo_;
    bool emprestado_;

public:
	ItemBiblioteca(int id, string titulo, int ano);
	
    virtual void exibirDetalhes();
    int getId();
    bool isEmprestado();
    void emprestar(int idLeitor);
    void devolver();
};

class Livro : public ItemBiblioteca {
protected:
	string autor_;
	string genero_;
	
public:
    Livro(int id, string titulo, int ano, string autor, string genero);      
    void exibirDetalhes() override;
    int getIdLeitor();
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

    int ultimoIdLivro = 0, ultimoIdUsuario = 0;

protected:
    bool validarNome(string nome);
    bool validarCriacaoDeLivro(string nomeLivro, string nomeAutor, string genero, int anoPublicacao);
    bool validarCriacaoDeUsuario(string nomeUsuario);
    bool validarResposta(string resposta);
    
    bool alunoExiste(int idAluno);
    bool professorExiste(int idProfessor);
    bool livroExiste(int idLivro);

    int registrarIdLivro();
    int registrarIdUsuario();

    bool palavraPossuiNumero(string palavra);

    void listarAlunos();
    void listarProfessores();

    bool validarEmprestimoParaAluno(Aluno& aluno, Livro& livro);
    bool validarEmprestimoParaProfessor(Professor& professor, Livro& livro);

    Aluno& obterAlunoPorId(int id);
    Professor& obterProfessorPorId(int id);
    Livro& obterLivroPorId(int id);

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
            case 3:
                biblioteca.limparTela();
                biblioteca.adicionarUsuario();
                break;
            case 4:
                biblioteca.limparTela();
                biblioteca.listarUsuarios();
                break;
            case 5:
                biblioteca.limparTela();
                biblioteca.emprestarLivro();
                break;
            case 6:
                biblioteca.limparTela();
                biblioteca.devolverLivro();
                break;
            default: 
                cout << "\nERRO: Comando inválido\n";
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
	id_(id), titulo_(titulo), ano_(ano), emprestado_(false), idLeitor_(0){}
		
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
		
void ItemBiblioteca::emprestar(int idLeitor){
	emprestado_ = true;
    idLeitor_ = idLeitor;
}
		
void ItemBiblioteca::devolver(){
	emprestado_ = false;
    idLeitor_ = 0;
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
    cout << "Id do leitor: " << idLeitor_ << endl;
}

int Livro::getIdLeitor(){
    return idLeitor_;
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
}

bool Usuario::podeEmprestar(){
    return emprestimosAtuais_ < limiteEmprestimos_;
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

int Biblioteca::registrarIdUsuario(){
    ultimoIdUsuario++;
    return ultimoIdUsuario;
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

    if(validarCriacaoDeLivro(nomeLivro, nomeAutor, genero, anoPublicacao)){
        livros_.emplace_back(registrarIdLivro(), nomeLivro, anoPublicacao, nomeAutor, genero);
        cout << "\nLivro adicionado" << endl;
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }else{
        cout << "\nERRO: Valor indevido inserido" << endl;
        cin.clear();
        cin.ignore();
        cout << "\nPrescione ENTER para continuar... ";
        cin.get();
    }
}

void Biblioteca::listarLivros(){
    if(livros_.size() == 0){
        cout << "\nNão há livros listados";
    }else{
        cout << "-----------------Listagem de livros----------------" << endl;
        for(Livro livro: livros_){
            livro.exibirDetalhes();
        }
    }
    cout << "\nPrescione ENTER para continuar...";
    cin.get();
}

bool Biblioteca::palavraPossuiNumero(string palavra){
    for(char letra: palavra){
        if(isdigit(letra)){
            return true;
        }
    }
    return false;
}

bool Biblioteca::validarCriacaoDeUsuario(string nomeAluno){
    return !nomeAluno.empty() && !palavraPossuiNumero(nomeAluno);
}      

void Biblioteca::adicionarUsuario(){
    string tipoUsuario, nomeUsuario;
    cout << "\n-----------------Adicionar usuário----------------" << endl;
    cout << "Nome do usuário: ";
    getline(cin, nomeUsuario);
    cout << "Tipo de usuário (1. Aluno | 2. Professor): ";
    getline(cin, tipoUsuario);

    if((validarCriacaoDeUsuario(nomeUsuario)) && (stoi(tipoUsuario) > 0 && stoi(tipoUsuario) < 3)){
        if(stoi(tipoUsuario) == 1){
            alunos_.emplace_back(registrarIdUsuario(),nomeUsuario);
            cout << "\nAluno registrado" << endl;

        }else{
            professores_.emplace_back(registrarIdUsuario(),nomeUsuario);
            cout << "\nProfessor registrado" << endl;
        }
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));

    }else{
        cout << "\nERRO: Valor indevido inserido" << endl;
        cout << "\nPrescione ENTER para continuar... ";
        cin.get();
    }
}

void Biblioteca::listarAlunos(){
    if(alunos_.size() == 0){
        cout << "\nSem alunos cadastrados";
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }else{
        for(Aluno aluno: alunos_){
            aluno.exibirUsuario();
        }
        cout << "\nPrescione ENTER para continuar...";
        cin.get();
    }
}

void Biblioteca::listarProfessores(){
    if(professores_.size() == 0){
        cout << "\nSem professores cadastrados";
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }else{
        for(Professor professor: professores_){
            professor.exibirUsuario();
        }
        cout << "\nPrescione ENTER para continuar...";
        cin.get();
    }
}

void Biblioteca::listarUsuarios(){
    string tipoPesquisa;
    cout << "\n------------------Listar Usuários-----------------" << endl;
    cout << "Tipo de usuário (1: Aluno | 2: Professor): ";
    getline(cin, tipoPesquisa);

    switch(stoi(tipoPesquisa)){
        case 1:
            limparTela();
            listarAlunos();
            break;
        case 2:
            limparTela();
            listarProfessores();
            break;
        default:
            cout << "\nERRO: Tipo de usuário não existe";
            this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }
}

Aluno& Biblioteca::obterAlunoPorId(int id){
    for(Aluno& aluno: alunos_){
        if(aluno.getId() == id){
            return aluno;
        }
    }
}

Professor& Biblioteca::obterProfessorPorId(int id){
    for(Professor& professor: professores_){
        if(professor.getId() == id){
            return professor;
        }
    }
}

Livro& Biblioteca::obterLivroPorId(int id){
    for(Livro& livro: livros_){
        if(livro.getId() == id){
            return livro;
        }
    }
}

bool Biblioteca::validarEmprestimoParaAluno(Aluno& aluno, Livro& livro){
    return aluno.podeEmprestar() && !livro.isEmprestado();
}

bool Biblioteca::validarEmprestimoParaProfessor(Professor& professor, Livro& livro){
    return professor.podeEmprestar() && !livro.isEmprestado();
}

void Biblioteca::emprestarLivro(){
    int idLeitor, idLivro, tipoUsuario;

    cout << "\n----------------Empréstimo de livro---------------" << endl;

    cout << "Id do livro: ";
    cin >> idLivro;

    cout << "\nId do leitor: ";
    cin >> idLeitor;

    if(livroExiste(idLivro) && (alunoExiste(idLeitor) || professorExiste(idLeitor))){
        Livro& livro = obterLivroPorId(idLivro);
        if(alunoExiste(idLeitor)){
            Aluno& aluno = obterAlunoPorId(idLeitor);
            if(validarEmprestimoParaAluno(aluno, livro)){
                aluno.realizarEmprestimo();
                livro.emprestar(idLeitor);

                cout << "\nEmpréstimo realizado" << endl;
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
            }else{
                cout << "\nEmpréstimo não atende aos requisitos" << endl;
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
            }
        }else{
            Professor& professor = obterProfessorPorId(idLeitor);
            if(validarEmprestimoParaProfessor(professor, livro)){
                professor.realizarEmprestimo();
                livro.emprestar(idLeitor);

                cout << "\nEmpréstimo realizado" << endl;
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
            }else{
                cout << "\nEmpréstimo não atende aos requisitos" << endl;
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
            }
        }
    }else{
        cout << "\nLivro ou usuário não encontrado" << endl;
        this_thread::sleep_for(chrono::seconds(segundosDeEspera));
    }
}

void Biblioteca::devolverLivro(){
    int idLivro;

    cout << "\n----------------Devolução de livro---------------" << endl;

    cout << "Id do livro: ";
    cin >> idLivro;

    if(livroExiste(idLivro)){
        Livro& livro = obterLivroPorId(idLivro);
        if(livro.isEmprestado()){
            if(!(alunoExiste(livro.getIdLeitor())||professorExiste(livro.getIdLeitor()))){
                cout << "\nERRO: leitor do livro não encontrado" << endl;
                cout << "\nPrescione ENTER para continuar" << endl;
                cin.get();
            }
            if(alunoExiste(livro.getIdLeitor())){
                Aluno& aluno = obterAlunoPorId(livro.getIdLeitor());
                aluno.realizarDevolucao();
                livro.devolver();

                cout << "\nDevolução realizada" << endl;
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
            }
            if(professorExiste(livro.getIdLeitor())){
                Professor& professor = obterProfessorPorId(livro.getIdLeitor());
                professor.realizarDevolucao();
                livro.devolver();

                cout << "\nDevolução realizada" << endl;
                this_thread::sleep_for(chrono::seconds(segundosDeEspera));
            }
        }else{
            cout << "\nLivro não está em empréstimo" << endl;
            cout << "\nPrescione ENTER para continuar" << endl;
            cin.get();
        }
    }else{
        cout << "\nLivro não encontrado" << endl;
        cout << "\nPrescione ENTER para continuar" << endl;
        cin.get();
    }
    cin.ignore();
}

bool Biblioteca::validarResposta(string resposta){
    int respostaNumerica;
    try{
        respostaNumerica = stoi(resposta);
        return 7 > respostaNumerica && respostaNumerica > -1;
    }catch(...){
        return false;
    }
}

int Biblioteca::menu(){
    string resposta;
    cout << "\n---------------Sistema de Biblioteca--------------" << endl;
    cout << "1. Adicionar livro" << endl;
    cout << "2. Listar livros" << endl;
    cout << "3. Adicionar usuário" << endl;
    cout << "4. Listar usuários" << endl;
    cout << "5. Emprestar livro" << endl;
    cout << "6. Devolver livro" << endl;
    cout << "0. Sair do programa" << endl;
    cout << "\nEscolha uma opção: ";
    cin >> resposta;
    cin.ignore();

    return validarResposta(resposta) ? stoi(resposta) : -1;
}