#ifndef _CALCUL_HPP_
#define _CALCUL_HPP_

#include <iostream>
#include <map>
//#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

/**********************************************
 *définit une fonctions (et ses sous fonctions)
 *capable d'évaluer une expression mathématique sous forme de chaîne
 *et de renvoyer le résultat
 */

namespace calcul
{
    /**
     *exception signalant que la syntaxe de l'expression passée en paramètre
     *n'est pas valide
     */
    class syntax_exception : public exception
    {
        protected:
            string message;
            int position; //position du caractère ayant provoqué l'erreur
            //expression mathématique complète
            string chaine;

        public:
            syntax_exception() throw() { };
            syntax_exception(const string& message, const string& chaine = "", int position = string::npos) throw();
            syntax_exception(const syntax_exception& source) throw();

            const char* what() const throw();

            syntax_exception& operator=(const syntax_exception& source) throw();

            virtual ~syntax_exception() throw() { };
    };

    /**
     *exception levée lors d'une division par zéro
     */
    class division_by_zero_exception : public exception
    {
        public:
            division_by_zero_exception() throw() { };
            division_by_zero_exception(const division_by_zero_exception& source) throw() { };

            const char* what() const throw();

            division_by_zero_exception& operator=(const division_by_zero_exception& source) throw() { };

            virtual ~division_by_zero_exception() throw() { };
    };

    /**
     *exception levée lorsqu'une variable ou une fonction utilisée dans un calcul n'est pas définie
     */
    class undefined_symbol_exception : public exception
    {
        protected:
            string symbole; //le nom de la variable/fonction indéfinie

        public:
            undefined_symbol_exception(const string& symbole = "?") throw();
            undefined_symbol_exception(const undefined_symbol_exception& source) throw();

            const char* what() const throw();

            undefined_symbol_exception& operator=(const undefined_symbol_exception& source) throw();

            virtual ~undefined_symbol_exception() throw() { };
    };

    /**
     *Classe qui permet d'envelopper les exceptions qui ont sont levées lorsque l'évaluateur
     *parse une expression de fonction. Par exemple, si l'utilisateur définit la fonction f : (x^2 + 2x + 5)/(x-1)
     *et qu'il tape 2*_f(1)/2, il peut ne pas comprendre d'où vient l'erreur si le seul message qu'il obtient est "division by zero".
     *C'est encore plus un problème lorsqu'une erreur de syntaxe est présente dans la déclaration de la fonction.
     *Cette exception permet donc de palier à ce problèmes en encapsulant l'erreur de base et en rajoutant dans le message d'erreur final
     *la provenance de l'erreur : par exemple [in function f]division by zero
     */
    class fonction_error_wrapper_exception : public exception
    {
        protected:
            string nom; //le nom de la fonction d'où provient l'erreur
            string message_origine; //le message d'erreur d'origine

        public:
            fonction_error_wrapper_exception(const exception& erreur, const string& nom = "?") throw();
            fonction_error_wrapper_exception(const fonction_error_wrapper_exception& source) throw();

            const char* what() const throw();

            fonction_error_wrapper_exception& operator=(const fonction_error_wrapper_exception& source) throw();

            virtual ~fonction_error_wrapper_exception() throw() { };
    };

    #define ALGORITHMIC_FUNCTION number_type (*)(number_type)

    /**
     *Classe qui évalue une expression pour la parser sous forme de nombre.
     *le paramètre template number_type permet de l'utiliser aussi bien avec
     *des int, des doubles, des float, etc.
     *le constructeur seul ne fait qu'initialiser l'objet, le parsage de l'expression
     *se fait lors de la conversion en objet de type number_type (voir operator number_type())
     *ou de l'appel explicite à eval()
     */
    template<typename number_type, typename algorithmic_function = number_type (*)(number_type)>
    class expression_evaluator
    {
        /*public:
            typedef (number_type (*)(number_type)) algorithmic_function;*/

        protected:
            string expression; //l'expression à parser
            unsigned int index; //index utilisé lors du parsage
            map<char, number_type> variables; //variables pouvant être utilisées pour des expressions
            map<string, expression_evaluator<number_type> > fonctions; //fonctions définies par l'utilisateur
            map<string, algorithmic_function> fonctions_algo; //fonctions algorithmiques et prédéfinies

            //méthodes d'analyse et de parcours de la chaîne (voir le corps des méthodes
            //pour des commentaires plus détaillés)
            number_type somme(); //+ et -
            number_type prior(); //*, / et %
            number_type puissance(); // ^
            number_type terme(); //analyse les nombres à proprement dit

            bool more(); //si l'on est arrivé à la fin de la chaîne
            /*Fonction qui renvoie true s'il y a un signe multiplié implicite à la position courante,
             *comme par exemple dans 2x + 3ab(2 + 3z)d, c'est à dire lorsque des lettres, des nombres et/ou des parenthèses
             *se suivent sans opérateur*/
            bool implicit_mult();

        public:
            expression_evaluator() { };
            expression_evaluator(const string& expression);
            expression_evaluator(const expression_evaluator& source);

            string get_expression() const;
            /*cette fonction renvoie la valeur d'une variable, ou 0 si elle n'existe pas
             *pour vérifier qu'une variable existe, utiliser is_var_defined() au préalable, car une variable
             *existante peut très bien avoir pour valeur 0
             */
            number_type get_var(char variable) const;
            /*
             *renvoie l'expression d'une fonction définie par l'utilisateur
             */
            string get_function(const string& nom) const;
            /*
             *renvoie un pointeur de fonction vers une fonction "algorithmique" définie par l'utilisateur
             *ou prédéfinie (sinus, cosinus, etc...). Par algorithmique, j'entend une fonction qui ne peut être
             *définie seulement par une expression mathématique comme '2x+3', par exemple la fonction cosinus, partie entière
             *ou encore racine carrée.
             */
            algorithmic_function get_algorithmic_function(const string& nom) const;

            void set_expression(const string& expression);
            //permet d'assigner une valeur à une variable
            void set_var(char variable, number_type valeur);
            //permet d'assigner à une fonction son expression
            void set_function(const string& nom, const string& expression);
            //permet d'assigner à une fonction son algorithme
            void set_algorithmic_function(const string& nom, algorithmic_function fonction);

            bool is_var_defined(char variable) const;
            bool is_function_defined(const string& nom) const;

            //évalue l'expression et renvoie un nombre
            number_type eval();
            //vérifie la syntaxe. Lève une syntax_exception si celle-ci n'est pas valide
            void check_syntax() const throw(syntax_exception);

            //méthode de classification des caractères
            static bool is_digit(char caractere);
            static bool is_alpha(char caractere);
            static bool is_alphanum(char caractere);
            static bool is_operator(char caractere);
            static bool is_forbidden(char caractere);

            expression_evaluator& operator=(const expression_evaluator& source);
            operator number_type();

            ~expression_evaluator();
    };

    //fonctions d'adaptation permettant d'utiliser les fonctions usuelles comme cosinus, log, etc...
    //avec n'importe quel type générique number_type en effectuant les conversions nécessaires :
    template<typename number_type>
    number_type _abs_adapter(number_type parametre)
    {
        return (number_type)fabs((double)parametre);
    }


    template<typename number_type>
    number_type _acos_adapter(number_type parametre)
    {
        return (number_type)acos((double)parametre);
    }

    template<typename number_type>
    number_type _asin_adapter(number_type parametre)
    {
        return (number_type)asin((double)parametre);
    }

    template<typename number_type>
    number_type _atan_adapter(number_type parametre)
    {
        return (number_type)atan((double)parametre);
    }


    template<typename number_type>
    number_type _ceil_adapter(number_type parametre)
    {
        return (number_type)ceil((double)parametre);
    }


    template<typename number_type>
    number_type _exp_adapter(number_type parametre)
    {
        return (number_type)exp((double)parametre);
    }


    template<typename number_type>
    number_type _floor_adapter(number_type parametre)
    {
        return (number_type)floor((double)parametre);
    }


    template<typename number_type>
    number_type _log_adapter(number_type parametre)
    {
        return (number_type)log((double)parametre);
    }

    template<typename number_type>
    number_type _log10_adapter(number_type parametre)
    {
        return (number_type)log10((double)parametre);
    }


    template<typename number_type>
    number_type _cos_adapter(number_type parametre)
    {
        return (number_type)cos((double)parametre);
    }

    template<typename number_type>
    number_type _cosh_adapter(number_type parametre)
    {
        return (number_type)cosh((double)parametre);
    }

    template<typename number_type>
    number_type _sin_adapter(number_type parametre)
    {
        return (number_type)sin((double)parametre);
    }

    template<typename number_type>
    number_type _sinh_adapter(number_type parametre)
    {
        return (number_type)sinh((double)parametre);
    }

    template<typename number_type>
    number_type _tan_adapter(number_type parametre)
    {
        return (number_type)tan((double)parametre);
    }

    template<typename number_type>
    number_type _tanh_adapter(number_type parametre)
    {
        return (number_type)tanh((double)parametre);
    }

    ///////////////////////////////////////////////////////

    syntax_exception::syntax_exception(const string& message, const string& chaine, int position) throw() : exception()
    {
        this->message = message;
        this->chaine = chaine;
        this->position = position;
    }

    syntax_exception::syntax_exception(const syntax_exception& source) throw() : exception()
    {
        *this = source;
    }

    const char* syntax_exception::what() const throw()
    {
        string temp(message);
        //si un numéro de caractère est spécifié pour l'erreur syntaxique, on affiche le caractère en question
        //et sa position dans l'expression après le message d'erreur
        if(position != string::npos)
        {
            ostringstream sortie;
            sortie << position+1;
            temp.append("(caractère \'").append(chaine, position, 1).append("\', en position ").append(sortie.str()).append(")");
        }

        return temp.c_str();
    }

    syntax_exception& syntax_exception::operator=(const syntax_exception& source) throw()
    {
        message = source.message;
        chaine = source.chaine;
        position = source.position;
    }

    ///////////////////////////////////////////////////////////////////////////

    const char* division_by_zero_exception::what() const throw()
    {
        return "division par zéro";
    }

    ///////////////////////////////////////////////////////////////////////////

    undefined_symbol_exception::undefined_symbol_exception(const string& symbole) throw()
    {
        this->symbole = symbole;
    }

    undefined_symbol_exception::undefined_symbol_exception(const undefined_symbol_exception& source) throw()
    {
        *this = source;
    }

    const char* undefined_symbol_exception::what() const throw()
    {
        return string("\'").append(symbole).append("\' n'est pas défini.").c_str();
    }

    undefined_symbol_exception& undefined_symbol_exception::operator=(const undefined_symbol_exception& source) throw()
    {
        symbole = source.symbole;
    }

    ///////////////////////////////////////////////////////////////////////////

    fonction_error_wrapper_exception::fonction_error_wrapper_exception(const exception& erreur, const string& nom) throw()
    {
        this->message_origine = erreur.what();
        this->nom = nom;
    }

    fonction_error_wrapper_exception::fonction_error_wrapper_exception(const fonction_error_wrapper_exception& source) throw()
    {
        *this = source;
    }

    const char* fonction_error_wrapper_exception::what() const throw()
    {
        return string("[in function ").append(nom).append("]").append(message_origine).c_str();
    }

    fonction_error_wrapper_exception& fonction_error_wrapper_exception::operator=(const fonction_error_wrapper_exception& source) throw()
    {
        nom = source.nom;
        message_origine = source.message_origine;
    }

    ///////////////////////////////////////////////////////////////////////////

    template<typename number_type, typename algorithmic_function>
    expression_evaluator<number_type, algorithmic_function>::expression_evaluator(const string& expression)
    {
        this->expression = expression;

        //ajout des fonctions mathématiques de base
        fonctions_algo["abs"] = &_abs_adapter<number_type>;

        fonctions_algo["acos"] = &_acos_adapter<number_type>;
        fonctions_algo["asin"] = &_asin_adapter<number_type>;
        fonctions_algo["atan"] = &_atan_adapter<number_type>;

        fonctions_algo["ceil"] = &_ceil_adapter<number_type>;

        fonctions_algo["exp"] = &_exp_adapter<number_type>;

        fonctions_algo["floor"] = &_floor_adapter<number_type>;

        fonctions_algo["log"] = &_log_adapter<number_type>;
        fonctions_algo["log10"] = &_log10_adapter<number_type>;

        fonctions_algo["cos"] = &_cos_adapter<number_type>;
        fonctions_algo["cosh"] = &_cosh_adapter<number_type>;
        fonctions_algo["sin"] = &_sin_adapter<number_type>;
        fonctions_algo["sinh"] = &_sinh_adapter<number_type>;
        fonctions_algo["tan"] = &_tan_adapter<number_type>;
        fonctions_algo["tanh"] = &_tanh_adapter<number_type>;
    }

    template<typename number_type, typename algorithmic_function>
    expression_evaluator<number_type, algorithmic_function>::expression_evaluator(const expression_evaluator<number_type, algorithmic_function>& source)
    {
        *this = source;
    }

    template<typename number_type, typename algorithmic_function>
    number_type expression_evaluator<number_type, algorithmic_function>::somme()
    {
        /*on commence par séparer les termes via les signes + et -,
         *ceux qui ont la plus faible priorité. On calculera d'abord
         *ces termes indépendamment pour ensuite leur appliquer, en dernier lieu,
         *l'opérateur + ou -.
         */


        //à l'appel de la fonction, on considère que le premier élément est forcément
        //soit un nombre, soit une parenthèse : on appelle donc la méthode terme()
        //via la méthode prior() pour récupérer ce premier nombre.
        number_type retour = prior();

        //une fois obtenu un nombre, on cherche un signe + ou -
        //si on trouve, on appel les méthodes sous-jacente pour calculer
        //l'ensemble de la valeur qui sera ajoutée ou retranchée au final
        while(more() && (expression[index] == '+' || expression[index] == '-'))
        {
            ++index; //on avance d'un caractère
            if(expression[index-1] == '+')
                retour += prior();
            else
                retour -= prior();
        }

        /*si on arrive à la fin d'une parenthèse, on sort d'une sous-expression.
         *On avance donc la position courante pour que, lorsque l'on rend la main à
         *la fonction terme(), l'analyse de l'expression ne s'arrête pas prématurément
         *à cause du fait que comme la parenthèse n'est ni un opérateur, ni un nombre,
         *les fonctions rendraient la main une à une sans effectuer aucun traitement supplémentaire
         *Lorsqu'on enlève cette ligne par exemple, (5+(5+5)*2)*2 font 15 (en fait, seulement les
         *trois premiers 5 on été analysés et ajoutés) et non pas 50.
         */
        if(more() && expression[index] == ')')
            ++index;

        return retour;
    }

    template<typename number_type, typename algorithmic_function>
    number_type expression_evaluator<number_type, algorithmic_function>::prior()
    {
        number_type retour = puissance(); //on obtient le premier nombre de l'expression via puissance()

        /*une fois obtenu un nombre, on cherche un signe *, / ou %
         *on continue jusqu'à que le signe suivant ne soit ni un nombre ni un * ni un / ni un %
         *pour être sûr d'avoir effectué toutes les divisions/multiplications de l'expression
         *ou sous-expression. Ainsi la priorité est respectée et on rend la main à la fonction somme
         */
        bool implicite = false; //on doit savoir si la multiplication était implicite ou non pour avancer ou pas index
        while( more() && (expression[index] == '*' || expression[index] == '/' || expression[index] == '%' || (implicite = implicit_mult())) )
        {
            if(!implicite)
                ++index;
            if(expression[index-1] == '/')
            {
                number_type temp = puissance();
                if(temp == 0)
                    throw division_by_zero_exception();

                retour /= temp;
            }
            else if(expression[index-1] == '%')
                retour = (number_type) ((long long int)retour % (long long int)puissance());
            else
                retour *= puissance();

            /*on réinitialise implicite pour les prochains passages, car si expression[index] vaut '*' par exemple, l'instruction
             *implicite = implicit_mult() ne sera pas exécutée ; donc si au précédent passage implicite valait true, il garderait cette valeur
             *si on ne le remettait pas à false
             */
            implicite = false;
        }

        return retour;
    }

    template<typename number_type, typename algorithmic_function>
    number_type expression_evaluator<number_type, algorithmic_function>::puissance()
    {
        /*fonction qui regarde si dans l'expression ou sous-expression en cours
         *il n'y a pas de signe '^'. Elle est après la fonction prior() dans le chaînage
         *des appels car l'opérateur d'élévation à la puissance est le plus prioritaire
         */

        number_type retour = terme();

        while(more() && (expression[index] == '^'))
        {
            ++index;
            retour = (number_type)pow((double)retour, (double)terme());
        }

        return retour;
    }

    template<typename number_type, typename algorithmic_function>
    number_type expression_evaluator<number_type, algorithmic_function>::terme()
    {
        //c'est la fonction qui lit réellement les nombres
        //si on tombe sur une parenthèse ouvrante, on ré-analyse
        //cette sous-expression comme une nouvelle expression apparentière
        if(expression[index] == '(')
        {
            ++index;
            return somme();
        }
        else
        {
            number_type nombre;
            unsigned int index_depart = index;
            bool moins_unaire = false; //s'il y avait un moins unaire au début de l'expression

            //gestion du moins unaire : si l'on rencontre un moins lorsque les fonctions
            //appellantes veulent un nombre, on considère que c'est un moins unaire
            //on met un booléen à true puis on avance l'index courant
            if(expression[index] == '-')
            {
                moins_unaire = true;
                ++index;
                ++index_depart;
            }

            if(expression_evaluator<number_type, algorithmic_function>::is_operator(expression[index]))
                throw syntax_exception("plusieurs opérateurs se suivent", expression, index);

            if(expression[index] == '_')
            {
                //on avance la position courante jusqu'à la parenthèse ouvrante
                ++index;
                ++index_depart;

                for(; more() && expression[index] != '('; ++index) ;
                //on doit récupérer la valeur d'une fonction
                if(!more())
                    throw syntax_exception("Un nom de fonction doit être suivi d'une parenthèse ouvrante", expression, index_depart);

                string nom_fonction = expression.substr(index_depart, index-index_depart);
                typename map<string, /*expression_evaluator<number_type, algorithmic_function>::algorithmic_function*/ALGORITHMIC_FUNCTION>::iterator it1 = fonctions_algo.find(nom_fonction);
                typename map<string, expression_evaluator<number_type, algorithmic_function> >::iterator it2 = fonctions.find(nom_fonction);

                ++index; //on passe après la parenthèse
                number_type x_value = somme(); //on évalue indépendamment l'expression qui suit la fonction (c'est à dire la valeur de x)

                if(it1 != fonctions_algo.end())
                {
                    try {
                        nombre = (*(*it1).second)(x_value);
                    }
                    //il faut convertir les messages d'erreurs pour bien spécifier que l'erreur se trouve dans la définition de la fonction,
                    //et non pas dans la chaîne analysée en ce moment
                    catch(const exception& e)
                    {
                        throw fonction_error_wrapper_exception(e, nom_fonction);
                    }
                }
                else if(it2 != fonctions.end())
                {

                    //on met à jour les définitions de variables et de fonctions pour que la suite tout ça etc.
                    fonctions[nom_fonction].variables = variables;
                    fonctions[nom_fonction].fonctions = fonctions;
                    fonctions[nom_fonction].set_var('x', x_value);

                    try {
                        nombre = fonctions[nom_fonction].eval();
                    }
                    //il faut convertir les messages d'erreurs pour bien spécifier que l'erreur se trouve dans la définition de la fonction,
                    //et non pas dans la chaîne analysée en ce moment
                    catch(const exception& e)
                    {
                        throw fonction_error_wrapper_exception(e, nom_fonction);
                    }
                }
                else
                    throw undefined_symbol_exception(nom_fonction);
            }
            else if(expression_evaluator<number_type, algorithmic_function>::is_alpha(expression[index]))
            {
                char variable = expression[index];
                if(!is_var_defined(variable))
                    throw undefined_symbol_exception(string(&variable, 1));

                number_type valeur = get_var(variable);
                nombre = valeur;
                ++index;
            }
            else
            {
                //sinon, on lit le nombre à la position courante
                for(; more() && is_digit(expression[index]); ++index) ;

                string nombre_str(expression, index_depart, index-index_depart);
                istringstream entree(nombre_str);
                entree >> nombre;
            }

            if(moins_unaire)
                return -nombre;
            else
                return nombre;
        }
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::more()
    {
        return index < expression.length();
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::implicit_mult()
    {
        /*Vérifie s'il n'y a pas de signe multiplier implicite
         *avec des variables (comme par exemple 2a(3+2) ou encore (x+2)(x-3)bc
         *vérifications : si un chiffre et une lettre se suivent (ou l'inverse)
         *                si deux lettres se suivent
         *                si un chiffre/une lettre suivent une parenthèse fermante (ou précèdent une parenthèse ouvrante)
         *                si une parenthèse fermante et une parenthèse ouvrante se suivent
         */
        return ( (expression_evaluator<number_type, algorithmic_function>::is_digit(expression[index-1]) && expression_evaluator<number_type, algorithmic_function>::is_alpha(expression[index])) ||
                 (expression_evaluator<number_type, algorithmic_function>::is_alpha(expression[index-1]) && expression_evaluator<number_type, algorithmic_function>::is_digit(expression[index])) ||
                 (expression_evaluator<number_type, algorithmic_function>::is_alpha(expression[index-1]) && expression_evaluator<number_type, algorithmic_function>::is_alpha(expression[index])) ||
                 (expression_evaluator<number_type, algorithmic_function>::is_alphanum(expression[index-1]) && expression[index] == '(') ||
                 (expression[index-1] == ')' && expression_evaluator<number_type, algorithmic_function>::is_alphanum(expression[index])) ||
                 (expression[index-1] == ')' && expression[index] == '(') );
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_digit(char caractere)
    {
        return (caractere == '.' ||
                (caractere >= '0' && caractere <= '9'));
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_alpha(char caractere)
    {
        return (caractere >= 'a' && caractere <= 'z') || (caractere >= 'A' && caractere <= 'Z') || caractere == '_';
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_alphanum(char caractere)
    {
        return is_digit(caractere) || is_alpha(caractere);
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_operator(char caractere)
    {
        return (caractere == '+' || caractere == '-' || caractere == '%'
                || caractere == '*' || caractere == '/' || caractere == '^');
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_forbidden(char caractere)
    {
        return (!is_digit(caractere) && !is_operator(caractere) && !is_alpha(caractere)
                && caractere != '(' && caractere != ')' && caractere != ' ');
    }

    template<typename number_type, typename algorithmic_function>
    string expression_evaluator<number_type, algorithmic_function>::get_expression() const
    {
        return expression;
    }

    template<typename number_type, typename algorithmic_function>
    number_type expression_evaluator<number_type, algorithmic_function>::get_var(char variable) const
    {
        typename map<char, number_type>::const_iterator it = variables.find(variable);

        if(it == variables.end())
            return 0;
        else
            return (*it).second;
    }

    template<typename number_type, typename algorithmic_function>
    string expression_evaluator<number_type, algorithmic_function>::get_function(const string& nom) const
    {
        typename map<string, expression_evaluator<number_type, algorithmic_function> >::const_iterator it = fonctions.find(nom);

        if(it == fonctions.end())
            return "";
        else
            return (*it).second.get_expression();
    }

    template<typename number_type, typename algorithmic_function>
    algorithmic_function expression_evaluator<number_type, algorithmic_function>::get_algorithmic_function(const string& nom) const
    {
        typename map<string, /*expression_evaluator<number_type, algorithmic_function>::algorithmic_function*/ALGORITHMIC_FUNCTION>::const_iterator it = fonctions.find(nom);

        if(it == fonctions.end())
            return NULL;
        else
            return (*it).second;
    }

    template<typename number_type, typename algorithmic_function>
    void expression_evaluator<number_type, algorithmic_function>::set_expression(const string& expression)
    {
        this->expression = expression;
    }

    template<typename number_type, typename algorithmic_function>
    void expression_evaluator<number_type, algorithmic_function>::set_var(char variable, number_type valeur)
    {
        variables[variable] = valeur;
    }

    template<typename number_type, typename algorithmic_function>
    void expression_evaluator<number_type, algorithmic_function>::set_function(const string& nom, const string& expression)
    {
        //on créer une nouvelle fonction seulement si elle n'est pas déjà définie parmis les fonctions algorithmiques ou prédéfinies
        //pour éviter les conflits
        if(fonctions_algo.find(nom) == fonctions_algo.end())
            fonctions[nom] = expression;
    }

    template<typename number_type, typename algorithmic_function>
    void expression_evaluator<number_type, algorithmic_function>::set_algorithmic_function(const string& nom, algorithmic_function fonction)
    {
        //si la fonction existe déjà parmis les fonctions définies par l'utilisateur, on la supprime de la liste avant de l'insérer
        //parmis les fonctions algorithmiques
        typename map<string, expression_evaluator<number_type, algorithmic_function> >::iterator it = fonctions.find(nom);
        if(it != fonctions.end())
            fonctions.erase(it);
        fonctions_algo[nom] = fonction;
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_var_defined(char variable) const
    {
        return variables.find(variable) != variables.end();
    }

    template<typename number_type, typename algorithmic_function>
    bool expression_evaluator<number_type, algorithmic_function>::is_function_defined(const string& nom) const
    {
        return fonctions.find(nom) != fonctions.end() || fonctions_algo.find(nom) != fonctions_algo.end();
    }

    template<typename number_type, typename algorithmic_function>
    number_type expression_evaluator<number_type, algorithmic_function>::eval()
    {
        if(expression.find(' ') != string::npos)
            boost::algorithm::erase_all(expression, " "); //suppression des espaces

        check_syntax();
        index = 0;
        return somme();
    }

    template<typename number_type, typename algorithmic_function>
    void expression_evaluator<number_type, algorithmic_function>::check_syntax() const throw(syntax_exception)
    {
        if((expression_evaluator<number_type, algorithmic_function>::is_operator(expression[0]) && expression[0] != '-')
           || expression_evaluator<number_type, algorithmic_function>::is_operator(expression[expression.length()-1]))
            throw syntax_exception("l'expression commence ou se termine par un opérateur");

        register int i;
        register int compteur = 0;

        for(i = 0; i < expression.length(); ++i)
        {
            if(expression_evaluator<number_type, algorithmic_function>::is_forbidden(expression[i]))
                throw syntax_exception("caractère interdit", expression, i);
            if(expression[i] == '(')
                ++compteur;
            if(expression[i] == ')')
                --compteur;
        }

        if(compteur != 0)
            throw syntax_exception("le nombre de parenthèses ouvrantes ne correspond pas au nombres de parenthèses fermantes.");
    }

    template<typename number_type, typename algorithmic_function>
    expression_evaluator<number_type, algorithmic_function>& expression_evaluator<number_type, algorithmic_function>::operator=(const expression_evaluator<number_type, algorithmic_function>& source)
    {
        expression = source.expression;
        variables = source.variables;
        fonctions = source.fonctions;
        fonctions_algo = source.fonctions_algo;
    }

    template<typename number_type, typename algorithmic_function>
    expression_evaluator<number_type, algorithmic_function>::operator number_type()
    {
        return eval();
    }

    template<typename number_type, typename algorithmic_function>
    expression_evaluator<number_type, algorithmic_function>::~expression_evaluator()
    {
    }
}

#endif /* ndef _CALCUL_HPP_ */