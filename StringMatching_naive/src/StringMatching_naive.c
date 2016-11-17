/*
 ============================================================================
 Name        : StringMatching_Naive.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <sys/timeb.h>

#define STR_MAXLENGTH 16384

unsigned int findOccurrence(char *, unsigned int, char *, unsigned int);

int main(int argc, char * argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	char * text, *patt;
	unsigned int n, m;

	double   elapsed_time;
	int sec, millisec;
	struct timeb timebuffer;

	if ( argc != 3 )
		return EXIT_FAILURE;

	text = argv[1];
	n = strlen(text);
	patt = argv[2];
	m = strlen(patt);

	printf("Input: \"%s\", \"%s\"\n", text, patt);

	ftime( &timebuffer );
	sec = timebuffer.time;
	millisec = timebuffer.millitm;


	unsigned int pos = findOccurrence(text, n, patt, m);

	ftime( &timebuffer );
	sec = timebuffer.time - sec;
	millisec = timebuffer.millitm - millisec;
	millisec += sec*1000;
	elapsed_time = (double)millisec/1000;

	printf( "Elasped time: %lf\n", elapsed_time );

	printf("Found at %u\n", pos);

	return EXIT_SUCCESS;
}

unsigned int findOccurrence(char* t, unsigned int n, char * p, unsigned int m) {
	unsigned int pos, l;
	for(pos = 0; 0 < n - m + 1; ++pos) {
		for(l = 0; l < m; ++l) {
			if ( t[pos+l] != p[l] ) break;
		}
		if ( l == m )
			return pos;
	}
	return pos;
}

/* 10561
If thou beest he; But O how fall'n! how chang'd
From him, who in the happy Realms of Light
Cloth'd with transcendent brightness didst out-shine
Myriads though bright: If he Whom mutual league,
United thoughts and counsels, equal hope
And hazard in the Glorious Enterprize,
Joynd with me once, now misery hath joynd
In equal ruin: into what Pit thou seest
From what highth fall'n, so much the stronger prov'd
He with his Thunder: and till then who knew
The force of those dire Arms? yet not for those,
Nor what the Potent Victor in his rage
Can else inflict, do I repent or change,
Though chang'd in outward lustre; that fixt mind
And high disdain, from sence of injur'd merit,
That with the mightiest rais'd me to contend,
And to the fierce contention brought along
Innumerable force of Spirits arm'd
That durst dislike his reign, and me preferring,
His utmost power with adverse power oppos'd
In dubious Battel on the Plains of Heav'n,
And shook his throne. What though the field be lost?
All is not lost; the unconquerable Will,
And study of revenge, immortal hate,
And courage never to submit or yield:
And what is else not to be overcome?
That Glory never shall his wrath or might
Extort from me. To bow and sue for grace
With suppliant knee, and deifie his power,
Who from the terrour of this Arm so late
Doubted his Empire, that were low indeed,
That were an ignominy and shame beneath
This downfall; since by Fate the strength of Gods
And this Empyreal substance cannot fail,
Since through experience of this great event
In Arms not worse, in foresight much advanc't,
We may with more successful hope resolve
To wage by force or guile eternal Warr
Irreconcileable, to our grand Foe,
Who now triumphs, and in th' excess of joy
Sole reigning holds the Tyranny of Heav'n.
So spake th' Apostate Angel, though in pain,
Vaunting aloud, but rackt with deep despare:
And him thus answer'd soon his bold Compeer.
O Prince, O Chief of many Throned Powers,
That led th' imbattelld Seraphim to Warr
Under thy conduct, and in dreadful deeds
Fearless, endanger'd Heav'ns perpetual King;
And put to proof his high Supremacy,
Whether upheld by strength, or Chance, or Fate,
Too well I see and rue the dire event,
That with sad overthrow and foul defeat
Hath lost us Heav'n, and all this mighty Host
In horrible destruction laid thus low,
As far as Gods and Heav'nly Essences
Can perish: for the mind and spirit remains
Invincible, and vigour soon returns,
Though all our Glory extinct, and happy state
Here swallow'd up in endless misery.
But what if he our Conquerour, (whom I now
Of force believe Almighty, since no less
Then such could hav orepow'rd such force as ours)
Have left us this our spirit and strength intire
Strongly to suffer and support our pains,
That we may so suffice his vengeful ire,
Or do him mightier service as his thralls
By right of Warr, what e're his business be
Here in the heart of Hell to work in Fire,
Or do his Errands in the gloomy Deep;
What can it then avail though yet we feel
Strength undiminisht, or eternal being
To undergo eternal punishment?
Whereto with speedy words th' Arch-fiend reply'd.
Fall'n Cherube, to be weak is miserable
Doing or Suffering: but of this be sure,
To do ought good never will be our task,
But ever to do ill our sole delight,
As being the contrary to his high will
Whom we resist. If then his Providence
Out of our evil seek to bring forth good,
Our labour must be to pervert that end,
And out of good still to find means of evil;
Which oft times may succeed, so as perhaps
Shall grieve him, if I fail not, and disturb
His inmost counsels from thir destind aim.
But see the angry Victor hath recall'd
His Ministers of vengeance and pursuit
Back to the Gates of Heav'n: The Sulphurous Hail
Shot after us in storm, oreblown hath laid
The fiery Surge, that from the Precipice
Of Heav'n receiv'd us falling, and the Thunder,
Wing'd with red Lightning and impetuous rage,
Perhaps hath spent his shafts, and ceases now
To bellow through the vast and boundless Deep.
Let us not slip th' occasion, whether scorn,
Or satiate fury yield it from our Foe.
Seest thou yon dreary Plain, forlorn and wilde,
The seat of desolation, voyd of light,
Save what the glimmering of these livid flames
Casts pale and dreadful? Thither let us tend
From off the tossing of these fiery waves,
There rest, if any rest can harbour there,
And reassembling our afflicted Powers,
Consult how we may henceforth most offend
Our Enemy, our own loss how repair,
How overcome this dire Calamity,
What reinforcement we may gain from Hope,
If not what resolution from despare.
Thus Satan talking to his neerest Mate
With Head up-lift above the wave, and Eyes
That sparkling blaz'd, his other Parts besides
Prone on the Flood, extended long and large
Lay floating many a rood, in bulk as huge
As whom the Fables name of monstrous size,
Titanian, or Earth-born, that warr'd on Jove,
Briareos or Typhon, whom the Den
By ancient Tarsus held, or that Sea-beast
Leviathan, which God of all his works
Created hugest that swim th' Ocean stream:
Him haply slumbring on the Norway foam
The Pilot of some small night-founder'd Skiff,
Deeming some Island, oft, as Sea-men tell,
With fixed Anchor in his skaly rind
Moors by his side under the Lee, while Night
Invests the Sea, and wished Morn delayes:
So stretcht out huge in length the Arch-fiend lay
Chain'd on the burning Lake, nor ever thence
Had ris'n or heav'd his head, but that the will
And high permission of all-ruling Heaven
Left him at large to his own dark designs,
That with reiterated crimes he might
Heap on himself damnation, while he sought
Evil to others, and enrag'd might see
How all his malice serv'd but to bring forth
Infinite goodness, grace and mercy shewn
On Man by him seduc't, but on himself
Treble confusion, wrath and vengeance pour'd.
Forthwith upright he rears from off the Pool
His mighty Stature; on each hand the flames
Drivn backward slope thir pointing spires, and rowld
In billows, leave i'th' midst a horrid Vale.
Then with expanded wings he stears his flight
Aloft, incumbent on the dusky Air
That felt unusual weight, till on dry Land
He lights, if it were Land that ever burn'd
With solid, as the Lake with liquid fire;
And such appear'd in hue, as when the force
Of subterranean wind transports a Hill
Torn from Pelorus, or the shatter'd side
Of thundring Ætna, whose combustible
And fewel'd entrals thence conceiving Fire,
Sublim'd with Mineral fury, aid the Winds,
And leave a singed bottom all involv'd
With stench and smoak: Such resting found the sole
Of unblest feet.  Him followed his next Mate,
Both glorying to have scap't the Stygian flood
As Gods, and by thir own recover'd strength,
Not by the sufferance of supernal Power.
Is this the Region, this the Soil, the Clime,
Said then the lost Arch-Angel, this the seat
That we must change for Heav'n, this mournful gloom
For that celestial light? Be it so, since he
Who now is Sovran can dispose and bid
What shall be right: fardest from him is best
Whom reason hath equald, force hath made supream
Above his equals. Farewel happy Fields
Where Joy for ever dwells: Hail horrours, hail
Infernal world, and thou profoundest Hell
Receive thy new Possessor: One who brings
A mind not to be chang'd by Place or Time.
The mind is its own place, and in it self
Can make a Heav'n of Hell, a Hell of Heav'n.
What matter where, if I be still the same,
And what I should be, all but less then he
Whom Thunder hath made greater? Here at least
We shall be free; th' Almighty hath not built
Here for his envy, will not drive us hence:
Here we may reign secure, and in my choyce
To reign is worth ambition though in Hell:
Better to reign in Hell, then serve in Heav'n.
But wherefore let we then our faithful friends,
Th' associates and copartners of our loss
Lye thus astonisht on th' oblivious Pool,
And call them not to share with us their part
In this unhappy Mansion, or once more
With rallied Arms to try what may be yet
Regaind in Heav'n, or what more lost

So Satan spake, and him Beelzebub
Thus answer'd. Leader of those Armies bright,
Which but th' Onmipotent none could have foyld,
If once they hear that voyce, thir liveliest pledge
Of hope in fears and dangers, heard so oft
In worst extreams, and on the perilous edge
Of battel when it rag'd, in all assaults
Thir surest signal, they will soon resume
New courage and revive, though now they lye
Groveling and prostrate on yon Lake of Fire,
As we erewhile, astounded and amaz'd,
No wonder, fall'n such a pernicious highth.
He scarce had ceas't when the superiour Fiend
Was moving toward the shoar; his ponderous shield
Ethereal temper, massy, large and round,
Behind him cast; the broad circumference
Hung on his shoulders like the Moon, whose Orb
Through Optic Glass the Tuscan Artist views
At Ev'ning from the top of Fesole,
Or in Valdarno, to descry new Lands,
Rivers or Mountains in her spotty Globe.
His Spear, to equal which the tallest Pine
Hewn on Norwegian hills, to be the Mast
Of some great Ammiral, were but a wand,
He walkt with to support uneasie steps
Over the burning Marle, not like those steps
On Heavens Azure, and the torrid Clime
Smote on him sore besides, vaulted with Fire;
Nathless he so endur'd, till on the Beach
Of that inflamed Sea, he stood and call'd
His Legions, Angel Forms, who lay intrans't
Thick as Autumnal Leaves that strow the Brooks
In Vallombrosa, where th' Etrurian shades
High overarch't imbowr; or scatterd sedge
Afloat, when with fierce Winds Orion arm'd
Hath vext the Red-Sea Coast, whose waves orethrew
Busiris and his Memphian Chivalry,
While with perfidious hatred they pursu'd
The Sojourners of Goshen, who beheld
From the safe shore thir floating Carkases
And broken Chariot Wheels, so thick bestrown
Abject and lost lay these, covering the Flood,
Under amazement of thir hideous change.
He call'd so loud, that all the hollow Deep
Of Hell resounded. Princes, Potentates,
Warriers, the Flowr of Heav'n, once yours, now lost,
If such astonishment as this can sieze
Eternal spirits; or have ye chos'n this place
After the toyl of Battel to repose
Your wearied vertue, for the ease you find
To slumber here, as in the Vales of Heav'n?
Or in this abject posture have ye sworn
To adore the Conquerour? who now beholds
Cherube and Seraph rowling in the Flood
With scatter'd Arms and Ensigns, till anon
His swift pursuers from Heav'n Gates discern
Th' advantage, and descending tread us down
Thus drooping, or with linked Thunderbolts
Transfix us to the bottom of this Gulfe.
Awake, arise, or be for ever fall'n.
*/
