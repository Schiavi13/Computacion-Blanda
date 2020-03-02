enfermedad(gripa).
enfermedad(dengue).
enfermedad(gastritis).
sintoma(tos).
sintoma(fiebre).
sintoma(dolor_estomago).
sintoma(vomito).
sintoma(nauseas).
sintoma(sinositis).
sintoma(malestar_general).


sintomade(tos,gripa).
sintomade(fiebre,gripa).
sintomade(malestar_general,gripa).
sintomade(fiebre,dengue).
sintomade(vomito,dengue).
sintomade(nauseas,dengue).
sintomade(malestar_general,dengue).
sintomade(dolor_estomago,gastritis).
vacio([]).

sintomadegripa(A):- sintomade(A,gripa).

sintomadegastritis(A):- sintomade(A,gastritis).

sintomadedengue(A):- sintomade(A,dengue).



evaluargripa([A|B]):- sintomadegripa(A) | evaluargripa(B).
                    

evaluardengue([A|B]):- sintomadedengue(A) | evaluardengue(B).

evaluargastritis([A|B]):- sintomadegastritis(A) | evaluargastritis(B).





