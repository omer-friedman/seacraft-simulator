#include "Controller.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 2)
            throw tooFewArgumentsException();
        shared_ptr<Controller> controller(new Controller());
        controller->run(argv[1]);
    }
    catch(exception& e){
        cout << e.what() <<endl;
        exit(1);//TODO לבדוק שלא יוצא אחרי כל חריגה, אלא רק אחרי חריגות מסויימים כמו קובץ שגוי
    }
    return 0;
}