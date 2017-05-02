
package ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function;

import java.util.function.Function;

import ch.arc.cours.lamda.interfacefonctionelle.neu.existant.function.tools.Maison;

public class UseFunctionMap
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
		System.out.println("map : Function");

		mapping();
		}

	private static void mapping()
		{
		int prix = 1;
		int nbPiece = 2;
		int surface = 3;
		Maison maison = new Maison(prix, nbPiece, surface);

		printSurface(maison);
		printPrix(maison);
		printPiece(maison);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void mapPrint(Maison maison, Function<Maison, Integer> function)
		{
		int attribut = function.apply(maison);
		System.out.println(attribut);
		}

	/*------------------------------*\
	|*				lamda			*|
	\*------------------------------*/

	private static void printSurface(Maison maison)
		{
		// version : classe interne anonyme
			{
			Function<Maison, Integer> getSurface = new Function<Maison, Integer>()
				{

				@Override
				public Integer apply(Maison maison)
					{
					return maison.getSurface();
					}
				};
			mapPrint(maison, getSurface);
			}

		// Version : lamda dans variable
			{
			Function<Maison, Integer> getSurface = maison1 -> maison1.getSurface();
			mapPrint(maison, getSurface);
			}

		// Version : lamda
			{
			mapPrint(maison, maison1 -> maison1.getSurface());
			}
		}

	private static void printPiece(Maison maison)
		{
		// Version : lamda
			{
			mapPrint(maison, maison1 -> maison1.getNbPiece());
			}
		}

	private static void printPrix(Maison maison)
		{
		// Version : lamda
			{
			mapPrint(maison, maison1 -> maison1.getPrix());
			}
		}

	}