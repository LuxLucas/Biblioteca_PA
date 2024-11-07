#ifndef ITEM_BIBLIOTECA_H
#define ITEM_BIBLIOTECA_H
class ItemBiblioteca {
protected:
    int id, ano;
    string titulo;
    bool emprestado;

public:
	ItemBiblioteca(int id, string titulo, int ano);
	
    virtual void exibirDetalhes();
    int getId();
    bool isEmprestado();
    void emprestar();
    void devolver();
};
#endf // ITEM_BIBLIOTECA_H

#ifndef LIVRO_H
#define LIVRO_H
class Livro : public ItemBiblioteca {
protected:
	string autor;
	string genero;
	
public:
    Livro(int id, string titulo, int ano, string autor, string genero);      
    void exibirDetalhes() override;
};
#endif // LIVRO_H
