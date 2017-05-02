
package ch.arc.cours.lamda.b_foreach;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Consumer;

import org.junit.Assert;

public class UseForeEach
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
		System.out.println("foreach : vers les streams ...");

		foreachList();
		foreachArray();
		limite();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void foreachList()
		{
		List<Integer> list = Arrays.asList(1, 2, 3);
		System.out.println("Before = " + list);

		// standard
			{
			List<Integer> listCarer = new ArrayList<Integer>(list.size());

			for(Integer x:list)
				{
				listCarer.add(x * x);
				}

			System.out.println("After = " + listCarer);
			}

		// list.forEach : classe interne anonyme
			{
			List<Integer> listCarer = new ArrayList<Integer>(list.size());

			list.forEach(new Consumer<Integer>()
				{

				@Override
				public void accept(Integer x)
					{
					listCarer.add(x * x);
					}
				});

			System.out.println("After = " + listCarer);
			}

		// list.foreach, lamda
			{
			List<Integer> listCarer = new ArrayList<Integer>(list.size());

			list.forEach(x->listCarer.add(x*x));

			System.out.println("After = " + listCarer);
			}
		}

	/**
	 * foreachArray existe pas!
	 * Solution :  voir un array comme une liste !
	 */
	private static void foreachArray()
		{
		Integer[] tab = { 1, 2, 3 };
		List<Integer> list = Arrays.asList(tab); //asList permet de PERCEVOIR le tableau comme une liste. Utile car le tableau n'est PAS un objet.

		// list.foreach, lamda
			{
			List<Integer> listCarer = new ArrayList<Integer>(list.size());

			list.forEach(x->listCarer.add(x*x));

			System.out.println("After = " + listCarer);
			}
		}

	/**
	 * Defi : compter le nombre d'élément de la liste
	 * 		sans utiliser size
	 * 		avec list.foreach
	 */
	private static void limite()
		{
		List<Integer> list = Arrays.asList(1, 2, 3);

		// version naife: conflict Final. Dans une classe interne anonyme, on peut uniquement utiliser des variables externes FINALE.
		// cela évite les effets de bord
			{
			//			int count = 0;
			//			list.forEach(n -> count++);
			}

		// version avec classe custom Int (Integer mais alterable) La REFERENCE de count ne CHANGE PAS. On accède simplement à une de ses méthodes.
			{
			Int count = new Int(0);

			list.forEach(x->count.inc());

			Assert.assertTrue(count.intvalue() == list.size());
			}
		}

	}
