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

int getPos(std::fstream& file, int linenumber)
{
    char buf;
    int newlines = 0;
    int pos = 0;
    file.seekg(0, file.beg);

    while (file.get(buf))
    {
        pos++;

        if (buf == '\n')
            newlines++;

        if (newlines == linenumber)
            break;
    }

    return pos + 1;
}

int main(int argc, char *argv[])
{    
    //Do we need the GUI ?
    bool gui = true;
    bool dull = false;
    QString path;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (std::string(argv[i]).compare("--cli") == 0)
            {
                gui = false;
            }
            if (std::string(argv[i]).compare("--dull") == 0)
            {
                dull = true;
            }
            if (std::string(argv[i]).substr(std::string(argv[i]).length() - 4) == ".txt")
            {
                #if (defined (_WIN32) || defined (_WIN64))
                    TCHAR cwd[255];
                    if (GetCurrentDirectory(255, cwd) != 0)
                    {
                        for (int i = 0; i < 255; i++)
                        {
                            if (cwd[i] != '\0')
                                path.append(static_cast<char>(cwd[i]));
                            else
                                break;
                        }

                        path.append('\\');
                        path.append(QString(argv[i]));
                    }
                    else
                    {
                        std::cout << "GetCurrentDirectory() error" << std::endl;
                    }
                #elif (defined (LINUX) || defined (__linux__))
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

    int lines = 0;

    //Seed the Random Number God
    srand( static_cast<unsigned int>(time(nullptr)) );

    //Begin Qt
    QApplication app(argc, argv);


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

            path = QFileDialog::getOpenFileName(nullptr, "Ouvrir...", QString(buf.c_str()), QString("All files (*.*)"));

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

    for (int i = 0; i < randInt(0, lines); i++)
    {
        getline(file, line);
    }

    struct Victim who;

    unsigned int pos = 0;
    std::stringstream ssbuf;
    for (unsigned int i = 0; i < line.length(); i++)
    {
        if (line[i] != ',')
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
        if (line[i] != ',')
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

    for (unsigned int i = pos; i < line.length(); i++)
    {
        if (line[i] != ',')
        {
            ssbuf << line[i];
        }
        else
        {
            pos = i+1;
            break;
        }
    }
    who.id = ssbuf.str();
    ssbuf.str(std::string());

    file.close();

    std::stringstream msg;
    if (!dull)
        #if (defined (_WIN32) || defined (_WIN64))
            msg << "ALERTE: Nous recherchons actuellement le dangereux individu répondant au nom de ";
        #elif (defined (LINUX) || defined (__linux__))
            if (!gui)
                msg << RED << "ALERTE: " << RESET << "Nous recherchons actuellement le dangereux individu répondant au nom de ";
            else
                msg << "ALERTE: Nous recherchons actuellement le dangereux individu répondant au nom de ";
        #endif
    else
        #if (defined (_WIN32) || defined (_WIN64))
            msg << "TARGET ACQUIRED: ";
        #elif (defined (LINUX) || defined (__linux__))
            msg << RED << "TARGET ACQUIRED: " << RESET;
        #endif

    msg << who.fname << " " << who.lname;

    if (!dull)
        msg << " pour les chefs d'accusations suivants:" << std::endl;
    else
        msg << std::endl;

    //Humorous flavor text
    if (!dull)
    {
        std::string reasons[13];

        reasons[0] = "Délit de code non commenté";
        reasons[1] = "Refus d'obtempérer à un ordre l'invitant à fermer son PC";
        reasons[2] = "Traffic illégal de maxi galettes";
        reasons[3] = "Refus de boire du café";
        reasons[4] = "Utilisation d'Electron.js pour faire un Hello World";
        reasons[5] = "Pratique abusive de vannes sur les mères";
        reasons[6] = "Pratique de Fortnite";
        reasons[7] = "Délit d'orthographe merdique sur Discord";
        reasons[8] = "Présentation de sale";
        reasons[9] = "Utilisation de Microsoft Edge sans permis";
        reasons[10] = "Délit de fuites de mémoire répétées";
        reasons[11] = "Téléchargement illégal de RAM";
        reasons[12] = "Propos injurieux envers le PHP";

        int accusations = randInt(1,5);
        std::string *rap_sheet = new std::string [static_cast<unsigned long>(accusations)];

        for (int i = 0; i < accusations; i++)
        {
            int matches = 0;
            int why = randInt(0,12);

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
            msg << "\t- " << rap_sheet[i];

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
        QMessageBox::information(nullptr, "TARGET ACQUIRED", qmsg);
        return 0;
    }
}
