
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function;

import java.util.List;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function.tools.Maison;

public class MaisonManipulator
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * see chapter stream to see beautiful flexible optimized code
	 */
	public static int mapReduce(List<Maison> list, Function<Maison, Integer> function, BinaryOperator<Integer> operator, int initValue)
		{
		int value = initValue;
		for(Maison maison:list)
			{
			int attribut = function.apply(maison);
			value = operator.apply(value, attribut);
			}

		return value;
		}

	/**
	 * see chapter stream to see beautiful flexible optimized code
	 */
	public static int filterMapReduce(List<Maison> list, Predicate<Maison> predicate, Function<Maison, Integer> function, BinaryOperator<Integer> operator, int initValue)
		{
		int value = initValue;
		for(Maison maison:list)
			{
			if (predicate.test(maison))
				{
				int attribut = function.apply(maison);
				value = operator.apply(value, attribut);
				}
			}

		return value;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
