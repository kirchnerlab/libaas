import elementtree.ElementTree as ET
import sys

def printStringArray(begin, list):
	sys.stdout.write(begin)
	sys.stdout.write("{ \"")
	sys.stdout.write("\", \"".join(list))
	sys.stdout.write("\" };")
	sys.stdout.write("\n")

def printNumberArray(begin, list):
	sys.stdout.write(begin)
	sys.stdout.write("{ ")
	sys.stdout.write(", ".join(list))
	sys.stdout.write(" };")
	sys.stdout.write("\n")

def printSpecArrays(begin, pos, sites, classi):
	sys.stdout.write(begin)
	sys.stdout.write("{ ")
	for i in range(len(pos)):
		sys.stdout.write("{ \"" + pos[i] + "\", \"" + sites[i] + "\", \"" + classi[i] + "\" }")
		if (i+1==len(pos)):
			sys.stdout.write("\n")
		else:
			sys.stdout.write(",\n")
	sys.stdout.write("};")
	sys.stdout.write("\n")

tree = ET.parse("unimod.xml")

titles = []
fullNames = []
nSpecificities = []
specSites = []
specPositions = []
specClassifications = []
nDeltas = []
deltaSymbols = []
deltaNumbers = []
nAltNames = []
altNames = []

for parent in tree.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}mod"):
	titles.append(parent.attrib.get("title"))
	fullNames.append(parent.attrib.get("full_name"))
	iter = parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}specificity")
	nSpecificities.append(str(len(list(iter))))
	for specificity in iter:
		specSites.append(specificity.attrib.get("site"))
		specPositions.append(specificity.attrib.get("position"))
		specClassifications.append(specificity.attrib.get("classification"))
#		for neutralLoss in specificity.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}NeutralLoss"):
#			print neutralLoss.tag
#		for pepNeutralLoss in specificity.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}PepNeutralLoss"):
#			print pepNeutralLoss.tag
#	print len(list(parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}delta")))
	for delta in parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}delta"):
		iter = delta.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}element")
		nDeltas.append(str(len(list(iter))))
		for element in iter:
			deltaSymbols.append(element.attrib.get("symbol"))
			deltaNumbers.append(element.attrib.get("number"))
	iter = parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}alt_name")
	nAltNames.append(str(len(list(iter))))
	for altName in iter:
		altNames.append(altName.text)

sys.stdout.write("const libaas::Size nModifications = " + str(len(titles)) + ";\n")
printStringArray("const libaas::Char* titles[] = ", titles)
#printStringArray("const libaas::Char* fullNames[] = ", fullNames)
printNumberArray("const libaas::Size nSpecificities[] = ", nSpecificities)
printSpecArrays("const libaas::Char* specificities[][3] = ", specSites, specPositions, specClassifications)
printNumberArray("const libaas::Size nDeltas[] = ", nDeltas)
printStringArray("const libaas::Char* deltaSymbols[] = ", deltaSymbols)
printNumberArray("const libaas::Double deltaNumbers[] = ", deltaNumbers)
#printNumberArray("const libaas::Size nAltNames[] = ", nAltNames)
#printStringArray("const libaas::Char* altNames[] = ", altNames)
