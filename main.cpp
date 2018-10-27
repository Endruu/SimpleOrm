#include "SQLiteConnection.hpp"

#include "Example.hpp"

#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <deque>
#include <list>

IConnection& operator>>(IConnection& conn, std::vector<Example>& exs)
{
    auto stmt = conn.query("SELECT ex_int, ex_text FROM ex_table");

    while (stmt->readNextRow())
    {
        Example ex;

        //stmt->getValue(0, ex.ExInt);
        //stmt->getValue(1, ex.ExString);

		//StatementExtractor(*stmt) >> ex.ExInt >> ex.ExString;

		*stmt >> ex.ExInt >> ex.ExString;

        exs.push_back(std::move(ex));
    }

    return conn;
}

template<typename T>
struct Loadable
{

	T load(StatementExtractor& stmt);
};

auto& extract(StatementExtractor& ext, Example& ex) { ext >> ex.ExInt >> ex.ExString; return ex; }

const char* queryString(const Example&) { return "SELECT ex_int, ex_text FROM ex_table"; }

template<class OutputIt>
void load(IConnection& conn, OutputIt first)
{
	auto stmt = conn.query("SELECT ex_int, ex_text FROM ex_table");

	while (stmt->readNextRow())
	{
		//typename std::iterator_traits<OutputIt>::value_type ex;
		typename OutputIt::container_type::value_type ex;
		*stmt >> ex.ExInt >> ex.ExString;
		*first++ = ex;
	}
}

template<class OutputIt>
void load2(IConnection& conn, OutputIt first)
{
	typename OutputIt::container_type::value_type ex;

	auto stmt = conn.query(queryString(ex));

	while (stmt->readNextRow())
	{
		*first++ = extract(StatementExtractor(*stmt), ex);
	}
}

template<typename CollectionT>
auto load(IConnection& conn)
{
	CollectionT collection;
	load(conn, std::back_inserter(collection));
	return collection;
}

int main()
{
    // const auto db = SqliteDb("db_path") ;
    // const auto rows = loadRows<Example>(db);

    std::cout << "BEGIN!" << std::endl;


    try
    {

    std::unique_ptr<IConnection> conn = std::make_unique<SQLiteConnection>(R"(E:\MyPlayground\Cpp\SimpleOrm\test_db.db)");

    std::vector<Example> rows1;
	

    *conn >> rows1;

    for(const auto& ex : rows1)
    {
        std::cout << "Example: " << ex.ExInt  << ' ' << ex.ExString << '\n';
    }

	std::deque<Example> rows2;

	//load(*conn, std::front_inserter(rows2));
	load2(*conn, std::front_inserter(rows2));

	//decltype(*std::front_inserter(rows2)) a;

	for (const auto& ex : rows2)
	{
		std::cout << "Example2: " << ex.ExInt << ' ' << ex.ExString << '\n';
	}

	auto rows3 = load<std::list<Example>>(*conn);
	for (const auto& ex : rows3)
	{
		std::cout << "Example3: " << ex.ExInt << ' ' << ex.ExString << '\n';
	}

    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "TADA!" << std::endl;
}