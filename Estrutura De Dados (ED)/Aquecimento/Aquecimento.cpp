#include "Rafael_Lins_Pinheiro.hpp" // implementa��es do professor.. fa�a seu pr�prio arquivo .hpp!

#define CATCH_CONFIG_MAIN // catch2 main()
#include "catch.hpp"

// =======================
// testes para exerc�cio 0
// -----------------------

TEST_CASE("ex0 - caso 0")
{
	REQUIRE(exercicio0("") == 0);
}

// =======================
// testes para exerc�cio 1
// -----------------------

TEST_CASE("ex1 a=1 b=3")
{
	REQUIRE(exercicio1("1 3") == 6);
}

TEST_CASE("ex1 a=1 b=10")
{
	REQUIRE(exercicio1("1 10") == 55);
}

// ===================
// testes para exemplo
// -------------------



// testado com Catch v2.13.1
// mais testes vir�o aqui no futuro...