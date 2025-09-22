/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/09/21 15:34:14 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <assert.h>

#include "wildcards.h"

// #define V1

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;
	size_t	i;

	i = 0;
	slen = strlen(s);
	if (start >= slen)
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		return (ptr[0] = '\0', ptr);
	}
	if (len > slen - start)
		len = slen - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[i + start] && (i < len))
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/***************************************************************************************************/




char	*next_sample(char **path)
{
	char	*ptr;
	char	*new_sample;

	while (*path && isasterisk(**path))
		(*path)++;
	ptr = *path;
	while (**path && !isasterisk(**path))
		(*path)++;
	return (ft_substr(ptr, 0, *path - ptr));
}

char	*find_match(char *ptested, char *psample)
{
	if (psample)
		return (strstr(ptested, psample));
	else
		return (NULL);
}

char	*align_ptested(char *ptested, char *psample)
{
	int		n;

	n = strlen(psample);
	while (ptested && *ptested && n-- > 0)
	{
		if (*++ptested == '\0')
			return (ptested);
		else if (!ptested)
			return (NULL);
	}
	return (ptested);
}

int	pathmatch(char *ptested, char *pref)
{
	char	*psample;
	
	while (1)
	{
		if (!iswildcard(pref))
		{
			if ((!*pref))
				return (1);
			else
			{
				if (!ptested || strcmp(ptested, pref))
					return (0);
				else
					return (1);
			}
		}
		else
		{
			psample = next_sample(&pref);
			if (!*psample)
				return (1);
			ptested = find_match(ptested, psample);
			if (!ptested)
				return (0);
			ptested = align_ptested(ptested, psample);
			pathmatch(ptested, pref);
		}
	}
	return (1);
}

#ifdef V0

int	main(void)
{
	char	*a, *b;
	while (scanf("%s %s", a, b))
	{
		int	cmp = pathmatch(a, b);
		printf("%d\n", cmp);
	}

	
	return (0);
}

#endif

#ifdef V1

void test_matches() {
    printf("=== TESTS QUI MATCHENT ===\n");
    
    // Tests basiques
    assert(pathmatch("hello.txt", "*.txt") == 1);
    assert(pathmatch("script.sh", "script.*") == 1);
    assert(pathmatch("README", "*ME") == 1);
    assert(pathmatch("file123", "file*") == 1);
    assert(pathmatch("test", "*") == 1);
    
    // Tests avec plusieurs astérisques
    assert(pathmatch("abcdefg", "abc*f*") == 1);
    assert(pathmatch("hello_world.c", "*_*.*") == 1);
    assert(pathmatch("my_long_filename", "my_*_*name") == 1);
    assert(pathmatch("configuration.conf", "*fig*.*") == 1);
    
    // Tests début/milieu/fin
    assert(pathmatch("prefix_suffix", "prefix_*") == 1);
    assert(pathmatch("middle_test", "*_test") == 1);
    assert(pathmatch("start_middle_end", "start_*_end") == 1);
    assert(pathmatch("document.pdf", "*ment.pdf") == 1);
    
    // Tests edge cases
    assert(pathmatch("a", "*") == 1);
    assert(pathmatch(".hidden", ".*") == 1);
    assert(pathmatch("file.tar.gz", "*.tar.*") == 1);
    assert(pathmatch("x.y.z", "*.*.*") == 1);
    assert(pathmatch("single", "*single*") == 1);
    
    // Tests sans wildcard (exact match)
    assert(pathmatch("exact", "exact") == 1);
    assert(pathmatch("test.c", "test.c") == 1);
    
    printf("Tous les tests de matching passent!\n\n");
}

// Tests qui NE DOIVENT PAS fonctionner (retourner 0)
void test_no_matches() {
    printf("=== TESTS QUI NE MATCHENT PAS ===\n");
    
    // Mauvaises extensions
    assert(pathmatch("hello.txt", "*.sh") == 0);
    assert(pathmatch("script.py", "*.c") == 0);
    
    // Préfixes qui ne matchent pas
    assert(pathmatch("hello.txt", "bye*") == 0);
    assert(pathmatch("README", "INSTALL*") == 0);
    
    // Suffixes qui ne matchent pas
    assert(pathmatch("file123", "*456") == 0);
    assert(pathmatch("test_file", "*_other") == 0);
    
    // Patterns qui ne peuvent pas matcher
    assert(pathmatch("abc", "*xyz*") == 0);
    assert(pathmatch("hello", "*world*") == 0);
    assert(pathmatch("short", "*very_long_pattern*") == 0);
    
    // Tests avec parties manquantes
    assert(pathmatch("start_end", "start_*_middle_*_end") == 0);
    assert(pathmatch("a.b", "a.b.c*") == 0);
    
    // Exact match qui échoue
    assert(pathmatch("exact", "Exact") == 0);
    assert(pathmatch("test.c", "test.h") == 0);
    assert(pathmatch("file", "FILE") == 0);
    
    // Cas vides/NULL (si ta fonction les gère)
    // assert(pathmatch("", "*") == 1);  // Dépend de ton implémentation
    // assert(pathmatch("test", "") == 0);
    
    printf("Tous les tests de non-matching passent!\n\n");
}

// Tests de cas limites
void test_edge_cases() {
    printf("=== TESTS DE CAS LIMITES ===\n");
    
    // Multiples astérisques consécutives (selon ton implémentation)
    assert(pathmatch("hello", "**hello**") == 1);
    assert(pathmatch("test", "***") == 1);
    
    // Patterns complexes
    assert(pathmatch("a_b_c_d", "*_*_*_*") == 1);
    assert(pathmatch("1x2y3z", "*x*y*z") == 1);
    
    // Échecs sur patterns complexes
    assert(pathmatch("a_b_c", "*_*_*_*") == 0);  // Pas assez de segments
    assert(pathmatch("1x2z3", "*x*y*z") == 0);   // y manquant
    
    printf("Tests de cas limites terminés!\n\n");
}

int main() {
    test_matches();
    test_no_matches();
    test_edge_cases();
    
    printf("🎉 TOUS LES TESTS SONT PASSÉS!\n");
    return 0;
}

#endif

#ifdef V2

void test_hardcore_patterns() {
    printf("=== TESTS HARDCORE ===\n");
    
    // Patterns avec répétitions de caractères
    assert(pathmatch("aaabbbccc", "a*b*c*") == 1);
    assert(pathmatch("aaabbbccc", "*a*b*c*") == 1);
    assert(pathmatch("xaaabbbcccx", "*a*b*c*") == 1);
    assert(pathmatch("abcabc", "*abc*abc*") == 1);
    
    // Patterns très ambigus
    assert(pathmatch("abcabc", "a*c*c") == 1);  // deux façons de matcher 'c'
    assert(pathmatch("abcdabcd", "a*d*d") == 1); // deux 'd' possibles
    assert(pathmatch("ababab", "*ab*ab*") == 1);
    
    // Overlapping patterns difficiles
    assert(pathmatch("abcdefabcdef", "*abc*def*abc*def*") == 1);
    assert(pathmatch("abababab", "*abab*abab*") == 1);
    assert(pathmatch("123412341234", "*1234*1234*") == 1);
    
    // Patterns qui échouent subtilement
    assert(pathmatch("abcdef", "*ace*") == 0);  // 'a' et 'e' pas dans l'ordre
    assert(pathmatch("abc", "*abcd*") == 0);    // 'd' manquant
    assert(pathmatch("abcabc", "*abc*xyz*") == 0); // 'xyz' impossible
    
    printf("Tests hardcore de base OK\n");
}

void test_edge_cases_extreme() {
    printf("=== CAS LIMITES EXTRÊMES ===\n");
    
    // Chaînes avec caractères répétés
    assert(pathmatch("aaaaaaaaaa", "a*a*a*a*a") == 1);
    assert(pathmatch("aaaaaaaaaa", "*a*a*a*a*a*") == 1);
    assert(pathmatch("abababababab", "*ab*ab*ab*ab*") == 1);
    
    // Patterns très longs avec beaucoup d'astérisques
    assert(pathmatch("abcdefghijk", "a*b*c*d*e*f*g*h*i*j*k") == 1);
    assert(pathmatch("abcdefghijk", "*a*b*c*d*e*f*g*h*i*j*k*") == 1);
    
    // Cas où l'ordre compte vraiment
    assert(pathmatch("fedcba", "*a*b*c*d*e*f*") == 0);  // ordre inversé
    assert(pathmatch("abcdef", "*f*e*d*c*b*a*") == 0);  // ordre inversé
    
    // Patterns avec caractères en fin qui peuvent être manqués
    assert(pathmatch("hello_world_test", "*world*test") == 1);
    assert(pathmatch("hello_world_test", "*world*missing") == 0);
    
    printf("Cas limites extrêmes OK\n");
}

void test_algorithmic_stress() {
    printf("=== STRESS ALGORITHMIQUE ===\n");
    
    // Tests qui peuvent causer backtracking excessif
    assert(pathmatch("aaaaaaaaaab", "*a*a*a*a*a*b") == 1);
    assert(pathmatch("aaaaaaaaaac", "*a*a*a*a*a*b") == 0);
    
    // Patterns qui forcent à tester plusieurs possibilités
    assert(pathmatch("abcabcabc", "*abc*abc*abc*") == 1);
    assert(pathmatch("abcabcab", "*abc*abc*abc*") == 0);
    
    // Cas où le premier match n'est pas le bon
    assert(pathmatch("abcdefabc", "*abc*def*") == 1);  // doit prendre le premier abc
    assert(pathmatch("defabcabc", "*abc*def*") == 0);  // def avant abc
    
    // Patterns avec beaucoup de choix possibles
    assert(pathmatch("a1b2c3d4e5", "*1*2*3*4*5*") == 1);
    assert(pathmatch("a1b2c3d4e6", "*1*2*3*4*5*") == 0);
    
    printf("Stress algorithmique OK\n");
}

void test_corner_cases() {
    printf("=== COINS TORDUS ===\n");
    
    // Un seul caractère avec patterns complexes
    assert(pathmatch("a", "*a*") == 1);
    assert(pathmatch("a", "*a*a*") == 0);  // deux 'a' requis
    
    // Patterns qui se chevauchent
    assert(pathmatch("ababa", "*aba*aba*") == 0);  // chevauchement possible
    assert(pathmatch("abab", "*aba*aba*") == 0);   // pas assez long
	assert(pathmatch("abaXaba", "*aba*aba*") == 1);
	assert(pathmatch("abacaba", "*aba*aba*") == 1);
    
    // Début et fin identiques
    assert(pathmatch("abcdefabc", "abc*abc") == 1);
    assert(pathmatch("abcdefdef", "abc*abc") == 0);
    
    // Patterns très courts sur chaînes longues
    assert(pathmatch("verylongstringwithlotsofcharacters", "*long*") == 1);
    assert(pathmatch("verylongstringwithlotsofcharacters", "*missing*") == 0);
    
    // Caractères spéciaux (si supportés)
    assert(pathmatch("file-name_test.tmp", "*-*_*.*") == 1);
    assert(pathmatch("file.name.test.tmp", "*.*.*.tmp") == 1);
    
    printf("Coins tordus OK\n");
}

void test_performance_killers() {
    printf("=== TUEURS DE PERFORMANCE ===\n");
    
    // Cas qui peuvent exploser exponentiellement
    assert(pathmatch("aaaaaaaaaa", "*a*a*a*a*a*a*a*a*a*a*") == 1);
    assert(pathmatch("ababababab", "*a*b*a*b*a*b*a*b*a*b*") == 1);
    
    // Patterns qui forcent beaucoup de backtracking
    assert(pathmatch("abcdefghij", "*a*b*c*d*e*f*g*h*i*j*") == 1);
    assert(pathmatch("abcdefghij", "*a*b*c*d*e*f*g*h*i*z*") == 0);
    
    // Répétitions qui peuvent boucler
    assert(pathmatch("abbbbbbbbbc", "a*b*c") == 1);
    assert(pathmatch("acccccccccc", "a*b*c") == 0);
    
    printf("Tueurs de performance OK\n");
}

int main() {
    test_hardcore_patterns();
    test_edge_cases_extreme();
    test_algorithmic_stress();
    test_corner_cases();
    test_performance_killers();
    
    printf("\n🔥 TOUS LES TESTS HARDCORE PASSÉS ! 🔥\n");
    printf("Ta fonction est SOLIDE !\n");
    
    return 0;
}

#endif