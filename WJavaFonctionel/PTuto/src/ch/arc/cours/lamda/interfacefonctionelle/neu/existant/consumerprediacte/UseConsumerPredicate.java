
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.consumerprediacte;

import java.util.function.Consumer;
import java.util.function.Predicate;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.consumerprediacte.tools.Homme;
import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.consumerprediacte.tools.HommeTools;

public class UseConsumerPredicate
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
		System.out.println("foreach & filter: Consumer & Predicate");

		foreachFilter();
		}

	private static void foreachFilter()
		{
		int n = 5;

		version1(n);

		// lamda
			{
			version2(n);
			version3(n);
			}
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void version1(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		System.out.println("Before :\t\t" + iterable);

		Predicate<Homme> predicate = new Predicate<Homme>()
			{

			@Override
			public boolean test(Homme homme)
				{
				return homme.getHauteur() > 25;
				}
			};

		Consumer<Homme> consumer = new Consumer<Homme>()
			{

			@Override
			public void accept(Homme homme)
				{
				homme.opposePoids();
				}
			};

		HommeManipulator.filterForeach(iterable, predicate, consumer);

		System.out.println("After Version 1 :\t" + iterable);
		}

	/*------------------------------*\
	|*				lamda			*|
	\*------------------------------*/

	/**
	 * lamda dans variable
	 */
	private static void version2(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		Predicate<Homme> hauteurBigger25 = homme -> homme.getHauteur() > 25;
		Consumer<Homme> opposePoids = homme -> homme.opposePoids();

		HommeManipulator.filterForeach(iterable, hauteurBigger25, opposePoids);

		System.out.println("After Version 2 :\t" + iterable);
		}

	/**
	 * lamda
	 */
	private static void version3(int n)
		{
		Iterable<Homme> iterable = HommeTools.create(n);

		HommeManipulator.filterForeach(iterable, homme -> homme.getHauteur() > 25, homme -> homme.opposePoids());

		System.out.println("After Version 3 :\t" + iterable);
		}

	}
