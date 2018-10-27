#include "SQLiteConnection.hpp"

#include "Example.hpp"

#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <deque>
#include <list>


auto& extract(StatementExtractor& ext, Example& ex) { ext >> ex.ExInt >> ex.ExString; return ex; }

const char* queryString(const Example&) { return "SELECT ex_int, ex_text FROM ex_table"; }

template<class OutputIt>
void load(IConnection& conn, OutputIt first)
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

    std::cout << "BEGIN!" << std::endl;

    try
    {

    std::unique_ptr<IConnection> conn = std::make_unique<SQLiteConnection>(R"(E:\MyPlayground\Cpp\SimpleOrm\test_db.db)");

    std::vector<Example> rows2;
	
	load(*conn, std::back_inserter(rows2));

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