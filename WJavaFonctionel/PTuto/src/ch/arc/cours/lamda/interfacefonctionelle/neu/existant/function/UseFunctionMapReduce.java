
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function;

import java.util.List;
import java.util.function.BinaryOperator;
import java.util.function.Function;

import org.junit.Assert;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function.tools.Maison;
import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function.tools.MaisonTools;

public class UseFunctionMapReduce
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		System.out.println("map reduce : Function binaryOperator ");

		mapReduce();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void mapReduce()
		{
		int n = 3;
		List<Maison> list = MaisonTools.create(n);

		int sum1 = version1(list);
		int sum2 = version2(list);
		int sum3 = version3(list);

		System.out.println(list);

		check(list, sum1);
		check(list, sum2);
		check(list, sum3);
		}

	/**
	 * somme des prix des maisons
	 *
	 * Classe Interne anonyme
	 */
	private static int version1(List<Maison> list)
		{
		BinaryOperator<Integer> somme = new BinaryOperator<Integer>()
			{

			@Override
			public Integer apply(Integer x, Integer y)
				{
				return x + y;
				}
			};
		Function<Maison, Integer> getPrix = new Function<Maison, Integer>()
			{

			@Override
			public Integer apply(Maison maison)
				{
				return maison.getPrix();
				}
			};
		return MaisonManipulator.mapReduce(list, getPrix, somme, 0);
		}

	/*------------------------------*\
	|*				lamda			*|
	\*------------------------------*/

	/**
	 * somme des prix des maisons
	 *
	 * lamda dans variable
	 */
	private static int version2(List<Maison> list)
		{
		BinaryOperator<Integer> somme = (x, y) -> x + y;
		Function<Maison, Integer> getPrix = maison -> maison.getPrix();
		return MaisonManipulator.mapReduce(list, getPrix, somme, 0);
		}

	/**
	 * somme des prix des maisons
	 *
	 * lamda
	 */
	private static int version3(List<Maison> list)
		{
		return MaisonManipulator.mapReduce(list, maison -> maison.getPrix(), (x, y) -> x + y, 0);
		}

	/*------------------------------*\
	|*				Tools			*|
	\*------------------------------*/

	private static void check(List<Maison> list, int sum)
		{
		System.out.println("sum prix = " + sum);

		int n = list.size();
		Assert.assertTrue(sum == n * (n + 1) / 2);
		}

	}
