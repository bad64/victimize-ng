#include "includes.h"

int randInt(int minvalue, int maxvalue)
{
    if (maxvalue == 0)
        return 0;

    return rand() % maxvalue + minvalue;
}

int getLines(std::fstream &file)
{
    int newlines = 0;
    std::string line;

    while (getline(file, line))
    {
        newlines++;
    }

    return newlines;
}

int main(int argc, char *argv[])
{    
    //Do we need the GUI ?
    bool gui = true;
    bool dull = false;
    QString path;
    QString locale = QLocale::system().name().section('_', 0, 0);

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (std::string(argv[i]).compare("--cli") == 0)
            {
                #if (defined (LINUX) || defined (__linux__))
                    gui = false;
                #endif
            }
            else if (std::string(argv[i]).compare("--dull") == 0)
            {
                dull = true;
            }
            else if (std::string(argv[i]).compare("--lang") == 0)
            {
                locale = QString(argv[i+1]);
            }
            else if ((std::string(argv[i]).length() > 4) && (argv[i][0] != '-'))
             {
                if (std::string(argv[i]).substr(std::string(argv[i]).length() - 4) == ".txt")
                {
                    #if (defined (LINUX) || defined (__linux__))
                        //Is this an absolute path or not ?
                        if (argv[i][0] == '/')
                        {
                            path = QString(argv[i]);
                        }
                        else
                        {
                            char cwd[255];
                            if(getcwd(cwd, sizeof(cwd)) != nullptr)
                            {
                                path = cwd;
                                path.append('/');
                                path.append(QString(argv[i]));
                            }
                            else
                            {
                                std::cout << "getcwd() error" << std::endl;
                            }
                        }
                    #endif
                }
           }
        }
    }

    int lines = 0;

    //Seed the Random Number God
    srand(static_cast<unsigned int>(time(nullptr)));

    //Begin Qt
    QApplication app(argc, argv);

    //Translation
    QTranslator translator;
    translator.load(":/translations/victimize_" + locale);
    app.installTranslator(&translator);

    if (path.isEmpty())
    {
        if (gui)
        {
            std::string buf;
            #if (defined (_WIN32) || defined (_WIN64))
                buf = getenv("USERPROFILE");
                buf.append("\\Documents");
            #elif (defined (LINUX) || defined (__linux__))
                buf = getenv("HOME");
            #endif

            path = QFileDialog::getOpenFileName(nullptr, QObject::tr("Ouvrir..."), QString(buf.c_str()), QString("All files (*.*)"));

            if (path.isEmpty())
                exit(0);
        }
        else
        {
            std::cout << "Usage: victimize <txt file>" << std::endl;
            exit(0);
        }
    }

    //Count the lines
    std::fstream file(path.toStdString().c_str(), std::ios::in);
    lines = getLines(file);

    //Get the victim
    file.close();
    file.open(path.toStdString().c_str(), std::ios::in);
    std::string line;

    for (int i = 0; i <= randInt(0, lines); i++)
    {
        getline(file, line);
    }

    struct Victim who;

    unsigned int pos = 0;
    std::stringstream ssbuf;
    for (unsigned int i = 0; i < line.length(); i++)
    {
        if ((line[i] != ',') && (line[i] !='\n'))
        {
            ssbuf << line[i];
        }
        else
        {
            pos = i+1;
            break;
        }
    }
    who.lname = ssbuf.str();
    ssbuf.str(std::string());

    for (unsigned int i = pos; i < line.length(); i++)
    {
        if ((line[i] != ',') && (line[i] !='\n'))
        {
            ssbuf << line[i];
        }
        else
        {
            pos = i+1;
            break;
        }
    }
    who.fname = ssbuf.str();
    ssbuf.str(std::string());

    file.close();

    std::stringstream msg;
    if (!dull)
        #if (defined (_WIN32) || defined (_WIN64))
            msg << QObject::tr("ALERTE: Nous recherchons actuellement le dangereux individu répondant au nom de ").toStdString();
        #elif (defined (LINUX) || defined (__linux__))
            if (!gui)
                msg << RED << QObject::tr("ALERTE: ").toStdString() << RESET << QObject::tr("Nous recherchons actuellement le dangereux individu répondant au nom de ").toStdString();
            else
                msg << QObject::tr("ALERTE: Nous recherchons actuellement le dangereux individu répondant au nom de ").toStdString();
        #endif
    else
    {
        if (!gui)
        {
            #if (defined (_WIN32) || defined (_WIN64))
                msg << QObject::tr("CIBLE ACQUISE: ").toStdString();
            #elif (defined (LINUX) || defined (__linux__))
                msg << RED << QObject::tr("CIBLE ACQUISE: ").toStdString() << RESET;
            #endif
        }
    }

    msg << who.fname << " " << who.lname;

    if (!dull)
        msg << QObject::tr(" pour les chefs d'accusations suivants:").toStdString() << std::endl;
    else
        msg << std::endl;

    //Humorous flavor text
    if (!dull)
    {
        std::string reasons[13];

        reasons[0] = QObject::tr("Délit de code non commenté").toStdString();
        reasons[1] = QObject::tr("Refus d'obtempérer à un ordre l'invitant à fermer son PC").toStdString();
        reasons[2] = QObject::tr("Traffic illégal de maxi galettes").toStdString();
        reasons[3] = QObject::tr("Refus de boire du café").toStdString();
        reasons[4] = QObject::tr("Utilisation d'Electron.js pour faire un Hello World").toStdString();
        reasons[5] = QObject::tr("Pratique abusive de vannes sur les mères").toStdString();
        reasons[6] = QObject::tr("Pratique de Fortnite").toStdString();
        reasons[7] = QObject::tr("Délit d'orthographe merdique sur Discord").toStdString();
        reasons[8] = QObject::tr("Présentation de sale").toStdString();
        reasons[9] = QObject::tr("Utilisation de Microsoft Edge sans permis").toStdString();
        reasons[10] = QObject::tr("Délit de fuites de mémoire répétées").toStdString();
        reasons[11] = QObject::tr("Téléchargement illégal de RAM").toStdString();
        reasons[12] = QObject::tr("Propos injurieux envers le PHP").toStdString();

        int accusations = randInt(1, 5);
        std::string *rap_sheet = new std::string [static_cast<unsigned long>(accusations)];

        for (int i = 0; i < accusations; i++)
        {
            int matches = 0;
            int why = randInt(0, 12);

            for (int j = 0; j < accusations; j++)
            {
                if (reasons[why] == rap_sheet[j])
                    matches++;
            }

            if (matches == 0)
                rap_sheet[i] = reasons[why];
            else
                i--;
        }

        msg << std::endl;

        for (int i = 0; i < accusations; i++)
        {
            msg << "    - " << rap_sheet[i];

            if (i != accusations -1)
                msg << std::endl;
        }
    }

    //Display all of it
    if (!gui)
    {
        std::cout << msg.str() << std::endl;
        return 0;
    }
    else
    {
        QString qmsg = QString::fromStdString(msg.str().c_str());
        QMessageBox::information(nullptr, QObject::tr("CIBLE ACQUISE"), qmsg);
        return 0;
    }
}
