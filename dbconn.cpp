#include <nanodbc/nanodbc.h>
#include <iostream>
#include <exception>
#include <cstdlib>

auto query = NANODBC_TEXT(
    "WITH totals AS (\r\n"
    "    SELECT\r\n"
    "        SUM(amount) AS total,\r\n"
    "        a.city_id\r\n"
    "    FROM\r\n"
    "        payment p,\r\n"
    "        customer c,\r\n"
    "        address a\r\n"
    "    WHERE\r\n"
    "        p.customer_id = c.customer_id\r\n"
    "        AND c.address_id = a.address_id\r\n"
    "    GROUP BY\r\n"
    "        a.city_id\r\n"
    ")\r\n"
    "SELECT\r\n"
    "    total,\r\n"
    "    city.city\r\n"
    "FROM\r\n"
    "    totals\r\n"
    "NATURAL JOIN city\r\n"
    "WHERE total >= ?\r\n";
);

int main(int argc, char* argv[]) try
{
    // ODBC connection string
    auto const connstr = std::getenv("ODBC_CONN_STR");

    if (connstr == nullptr)
    {
        std::cerr << "Connection string not supplied" << std::endl;
        return EXIT_FAILURE;
    }

    if (argc != 2)
    {
        std::cerr << "Query parameter not supplied" << std::endl;
        return EXIT_FAILURE;
    }
    
    int min_revenue = std::stoi(argv[1]);
    nanodbc::connection conn(connstr);

    nanodbc::statement stmt(conn, query);
    stmt.bind(0, &min_revenue);

    auto result = stmt.execute();
    std::cout << "These are the cities with revenue above " << min_revenue << ":" << std::endl;

    while (result.next())
    {
        auto total_revenue = result.get<int>(0);
        auto city_name     = result.get<std::string>(1);
        std::cout << city_name << "\r\n\t" << total_revenue << "\r\n";
    }

    std::cout << "\r\n" "(END)" << std::endl;
    
    return EXIT_SUCCESS;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
