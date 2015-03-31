#ifndef LBB_UTILITY_MOVE_H_
#define LBB_UTILITY_MOVE_H_

#include <lbb/meta.h>

//TODO : fucking DOC !!!!

/**
 * \file Move.h
 *
 * Move semantique, copy semantique et autre trucs.
 *
 * Quelques regles pour passer des arguments :
 *
 * Il est souvent recommandé de passer les arguments à une fonction par référence quand la fonction doit modifier le contenu passé
 * en parametre et par référence constante quand le contenu n'est pas altéré ou ne doit pas etre altéré :
 *
 * \code
 * struct Foo;
 *
 * void use_foo(const Foo&);
 *
 * void modify_foo(Foo&);
 * \endcode
 *
 * Cette approche fonctionne, mais elle n'est pas toujours optimale, il est courant qu'une fonction copie les arguments passé en entré
 * pour pouvoir travailler.
 *
 * \code
 * //prend une string en entrée et renvoi sa version en majuscule
 *
 * string capitalize(const string& to_capitalize) {
 * 	//COPY !!!!
 * 	string result = to_capitalize;
 * 	//... WORK ...
 *
 * 	return result;
 * }
 * \endcode
 *
 * Dans cette fonction, quoi qu'il arrive le parametre d'entrée to_capitalize va etre copié, une meilleure approche serait de passer ce
 * parametre par valeur :
 *
 * \code
 * //prend une string en entrée et renvoi sa version en majuscule
 *
 * string capitalize_by_value(string to_capitalize) {
 * 	//COPY !!!!
 * 	//... WORK ...
 *
 * 	return to_capitalize;
 * }
 * \endcode
 *
 * si l'on compare les deux versions :
 *
 * \code
 *
 * string foo("foo");
 *
 * //ANCIENNE VERSION
 * capitalize(foo);								//copie de foo
 * capitalize(string("bar"));					//copie de la string temporaire contenant bar
 *
 * //NOUVELLE VERSION
 * capitalize_by_value(foo);					//copie de foo
 * capitalize_by_value(string("bar"));			//passage SANS COPIE de la string temporaire contenant bar
 * \endcode
 *
 * Contrairement a l'appel par reference l'appel par valeur ne va PAS copier la tring temporaire crée par l'appel
 * a string("bar).
 *
 *
 * RVALUE, LVALUE, XVALUES, etc ..
 *
 * Le language c++ defini plusieurs types de valeur suivant leur "durée de vie" :
 * 	- Les valeurs faisant partie d'un scope, celles dont on peut prendre une adresse sont nommée LVALUES
 * 	- Les valeurs temporaires (souvent généré par un appel a une fonction) sont des rvalue, si elles nes sont
 * 	pas "attrapées" dans une lvalue par copie (assignement, constructeur de copie ou assignement a une reference),
 * 	elle sont detruites immediatement.
 *
 * 	Grosso modo :
 * 		- lvalue => addressable
 * 		- rvalue => temporaire (in the air)
 *
 * 	\code
 * 	string s;					//lvalue
 *
 * 	string do_stuff();			//renvoie une rvalue, besoin de l'attacher à une lvalue pour la conserver
 *
 * 	s = do_stuff();				// assignement d'une rvalue à une lvalue en utilisant l'operateur d'assignement
 * 	const string const_s = do_stuff();		// assignement d'une rvalue à une lvalue en utilisant le constructeur de copie
 * \endcode
 *
 * Cet exemple expose un probleme recurent en c++ : les copies regulieres de rvalue vers lvalue, en effet,
 * la fonction do_stuff() va creer une rvalue qui ensuite va etre copié dans la rvalue attendu, si la classe string
 * n'utilise pas le COW (copy on write), ce genre d'opération peut rapidement couter en ressources :
 *
 * 		- Creation de la string et allocation de son buffer dans do_stuff()
 * 		- reallocation ou creation du buffer de la lvalue cible
 * 		- copie du contenu du buffer de la rvalue dans celui de la lvalue
 * 		- destruction de la rvalue
 *
 *  Pour eviter ce genre de soucis, il est courament recommandé de passer la string par reference et de la modifier dans
 * 	la fonction cible :
 *
 * 	\code
 * 	string s;
 *
 * 	//renvoi une reference pour chainer les appels
 * 	string& do_stuff_by_reference(string& s);
 *
 * 	do_stuff_by_reference(s);
 *
 * 	//const_s ne peux PLUS etre const car elle doit etre passé en parametre et doit etre mutable !!!
 * 	string not_so_const_s;
 * 	do_stuff_by_reference(not_so_const_s);
 *
 * 	//si l'on veux garder la constance :
 * 	const string const_s = do_stuff_by_reference(string(""));				//IMPOSSIBLE, NE COMPILERA PAS !!!!
 * 	\endcode
 *
 * 	Cette approche n'est pas bonne car elle force l'utilisateur a allouer une string en tant que lvalue (une rvalue renvera une belle erreur de compilation)
 * 	avant d'appeler la fonction ce qui n'est pas syntaxiquement optimal.
 *
 * 	Une approche plus interessante serait de deplacer le contenu de la rvalue dans la lvalue plutot que de le copier
 *
 * 	Pour le constructeur de copie, les operations seraient alors les suivante :
 * 		- Creation de la string et allocation de son buffer dans do_stuff()
 * 		- copie du pointeur de buffer de la rvalue dans la lvalue
 * 		- mise a 0 du pointeur de la rvalue
 * 		- destruction de la rvalue
 *
 * 	Avec ce schema, une seule allocation est requise et le passage de parametre est beaucoup plus rapide et le code reste clair.
 *  Il pourait etre egalement interessant de pouvoir recycler les lvalue dont on ne se sert plus, qui arrivent a expiration :
 *
 *  \code
 *  string do_stuff() {
 *  	string result;
 *
 *  	// ... work on result ...
 *
 *  	return result;			//appel du constructeur de copie alors que result ne sera plus utilisé quoi qu'il arrive
 *  }
 *  \endcode
 *
 * On en arrive a un nouveau type de classification :
 *
 * \code
 * 									EXPRESSION
 * 									  /    \
 * 									 /      \
 *								GLVALUE    RVALUE
 *								   /  \    /  \
 *								  /    \  /    \
 * 							 LVALUE   XVALUE   PRVALUE
 * \endcode
 *
 * ou :
 * 	- GLVALUE : generalized lvalue (tout type de lvalue)
 * 	- LVALUE : une lvalue "en vie"
 * 	- RVALUE : une rvalue (tout type de rvalue)
 * 	- PRVALUE : PURE RVALUE une rvalue qui n'a pas été attrapé ou des literaux (12, 7.2, true, ...)
 * 	- XVALUE : une lvalue ou rvalue qui arrive a expiration
 *
 * Pour eviter les copies inutiles et transferer les ressources d'un objet a un autre,  il faudrait un moyen pour
 * attraper les xvalues. C'est ce que le framework lbb::move propose.
 *
 *
 * A propos de la copy elision :
 *
 * En fait, certains point montrés en exemple plus haut ne sont pas tout a fait vrai, le constructeur de copie
 * est une fonction spécial qui représente une construction a traver un autre objet et le compilateur peux optimiser
 * la copie dans certains contexte (12.8.15 de la norme c++03)
 *
 * When certain criteria are met, an implementation is allowed to omit the copy construction of a class object,
 * even if the copy constructor and/or destructor for the object have side effects. In such cases, the implementation
 * treats the source and target of the omitted copy operation as simply two different ways of referring to
 * the same object, and the destruction of that object occurs at the later of the times when the two objects
 * would have been destroyed without the optimization.111) This elision of copy operations is permitted in the
 * following circumstances (which may be combined to eliminate multiple copies):
 *
 * 	- in a return statement in a function with a class return type, when the expression is the name of a
 * 	non-volatile automatic object with the same cv-unqualified type as the function return type, the copy
 * 	operation can be omitted by constructing the automatic object directly into the function’s return value
 * 	- when a temporary class object that has not been bound to a reference (12.2) would be copied to a class
 * 	object with the same cv-unqualified type, the copy operation can be omitted by constructing the temporary
 * 	object directly into the target of the omitted copy
 *
 * Autrement dit :
 *
 * \code
 * string do_stuff() {
 * 	string result;			//construit dans la valeur de retour
 *
 * 	// ... WORK ...
 *
 * 	return result;			//=> pas de copie, en interne result est deja dans la valeur de retour
 * }
 *
 * string s = string("toto");			//pas de copie, rien ne reference la rvalue produite par string("toto")
 * string s = do_stuff();				// =>  pas de copie
 * \endcode
 *
 * Les compilateurs implementent cette optimisation depuis tres longtemps (gcc 2.95 et MSVS7 et avant partiellement ...),
 * c'est egallement un argument de poid pour le passage de parametres par valeur :
 *
 * \code
 * string do_stuff();
 *
 * void need_string_by_ref(const string& s) {
 * 	string foo(s);
 *
 * 	//WORK ... using foo
 * }
 *
 * void need_string(string s) {
 * 	//work using s
 * }
 *
 * string s;
 *
 * need_string_by_ref(s);					//copie
 * need_string_by_ref(do_stuff());			//copie
 *
 * need_string(s);							//copie
 * need_string(do_stuff());					//pas de copie ...
 * \endcode
 *
 *
 *
 *
 *
 * \endcode
 *
 * Apres cette introduction (necessaire), il est temps de passer aux choses serieuses :
 * lbb::utility::move
 *
 * Ce framework permet d'activer facillement des
 *
 *
 *
 *
 *
 */



namespace lbb {
namespace utility {

namespace move_ {

	/**
	 * Representation of an rvalue of T : an rvalue of T
	 * inherit from T and can not be instantiated (passage by reference only)
	 */
	template <class T>
	struct rvalue_ : public T, meta_type_<T> { };
}


/**
 * Return true if the type T is an rvalue and false otherwise
 */
template<typename T>
struct is_rvalue_ : false_ { };

template<typename T>
struct is_rvalue_<move_::rvalue_<T> > : true_ { };

/**
 * Return the type of the rvalue of T
 */
template<typename T>
struct rvalue_of_ : meta_type_<move_::rvalue_<T> > { };

/**
 * Return the type of the rvalue_reference of T
 */
template<typename T>
struct rvalue_reference_of_ : meta_type_<move_::rvalue_<T>&> { };


/**
 * If a class want to become movable, it should implement this protocol :
 *
 * \code
 * struct Foo : movable<Foo>
 * {
 * 		LBB_TYPEDEF_MOVE_TYPES(Foo);
 *
 * 		//regular constructor and copy constructor
 * 		Foo();
 * 		Foo(const Foo& to_copy);
 *
 * 		//Move constructor
 * 		Foo(rvalue_reference to_move);
 *
 * 	#if ASSIGNEMENT_BY_VALUE
 * 		Foo& operator=(Foo to_copy);						//copy and swap
 * 		Foo& operator=(rvalue_reference to_move);			//move assignment
 * 	#elif MOVE_ASSIGNEMENT_BY_EXPLICIT_MOVE
 * 		Foo& operator=(const Foo& to_copy);					//always implicitly call
 * 		Foo& operator=(rvalue_reference to_move);			//call when lbb::utility::move come into play
 * 	#elif FINE_GRAINED_CONTROL_OVER_ASSIGNEMENT
 * 		LBB_FORWARD_MOVE_REFERENCE_ASSIGNEMENT();			//forward to reference to const overload
 * 		template<typename T>
 * 		enable_if_<is_same_type_<T, const Foo>::value, Foo>::type&
 * 		operator=(T& to_copy);								//reference to const overload using enable_if_ discrimination .
 * 		Foo& operator=(rvalue_reference to_move);			//call when lbb::utility::move come into play
 * 	#endif
 *
 * }
 *
 */
template<typename T>
struct movable {
	typedef typename rvalue_of_<T>::type rvalue;

	//TODO other alias ...
	typedef typename rvalue_reference_of_<T>::type rvalue_reference;
	typedef const typename rvalue_reference_of_<T>::type const_reference;

	/**
	 * Implicit cast to an rvalue reference ...
	 */
	operator rvalue_reference()  {
		return *static_cast<rvalue*>(this);
	}

	/**
	 * implicit cast to a rvalue reference to const
	 */
	operator const_reference() const  {
		return *static_cast<const rvalue*>(this);
	}
};


/**
 * Return true if the type is movable and false otherwise
 */
template<typename T>
struct is_movable_ : bool_<is_derived_of_<T, movable<T> >::value> { };

/**
 * Move for type not movable ... it will just return a reference to const
 * @param input the xvalue to move
 * @return a reference to const (same as input ...)
 */
template<typename T>
typename disable_if_<is_movable_<T>::value,
const T>::type& move(const T& input) {
	return input;
}

/**
 * Move of movable
 * @param input the xvalue to move
 * @return the rvalue_reference
 */
template<typename T>
typename enable_if_<is_movable_<T>::value,
typename rvalue_reference_of_<T>::type>::type move(T& input) {
	return input;
}


/**
 * Move of movable
 * @param input the xvalue to move
 * @return the rvalue_reference to const
 */
template<typename T>
typename enable_if_<is_movable_<T>::value,
const typename rvalue_reference_of_<T>::type>::type move(const T& input) {
	return input;
}


/**
 * Move for type not movable ... it will just return a reference to const
 * @param input the xvalue to move
 * @return a reference to const (same as input ...)
 */
template<typename T>
typename disable_if_<is_movable_<T>::value, T>::type& 
forward(T& input) {
	return input;
}

/**
 * Move of movable
 * @param input the xvalue to move
 * @return the rvalue_reference
 */
template<typename T>
typename enable_if_<is_movable_<T>::value, T>::type 
forward(T& input) {
	return move(input);
}


/**
 * Move of movable
 * @param input the xvalue to move
 * @return the rvalue_reference to const
 */
template<typename T>
typename enable_if_<is_movable_<T>::value, const T>::type forward(const T& input) {
	return move(input);
}


}  // namespace utility
}  // namespace lbb

//forward (c)rvalue references types
#define LBB_TYPEDEF_MOVE_TYPES(TYPE)  typedef lbb::utility::rvalue_reference_of_<TYPE>::type rvalue_reference; \
	typedef const lbb::utility::rvalue_reference_of_<TYPE>::type crvalue_reference


//forward (c)rvalue references types (use inside template (dependent name)) ...
#define LBB_TYPEDEF_MOVE_TYPES_TPL(TYPE)  typedef typename lbb::utility::rvalue_reference_of_<TYPE>::type rvalue_reference; \
	typedef const typename lbb::utility::rvalue_reference_of_<TYPE>::type crvalue_reference


#define LBB_FORWARD_MOVE_REFERENCE_ASSIGNEMENT(TYPE) \
		TYPE& operator=(TYPE& to_copy) { \
		return (*this) = (const_reference) to_copy; \
	}


#define LBB_TAG_MOVABLE_BUT_NOT_COPYABLE(TYPE) \
		private: \
		TYPE(TYPE&); \
		TYPE& operator=(TYPE&)






#endif /* LBB_UTILITY_MOVE_H_ */
