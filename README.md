# dbconn

This is a simple app to demonstrate use of ODBC in C++ with use of
proper OOP wrappers.

## Running

To run this simple program use Docker Compose:

    docker compose up -d

Connect terminal to `app` container _or_ instanciate another
container with:

    docker compose run app

Now run program inside container:

    ./dbconn 100

The app should query DB for records with filter of `100` minimum
revenue value for fictional DVD rental network.

## Used materials

- This app uses nanodbc to access ODBC API in C++ fashion.
- To demonstrate query functionality I use Pagila sample database.
- Running on all platforms is done with use of Docker.
