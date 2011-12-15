import elementtree.ElementTree as ET
import sys

def printStringArray(begin, list):
	sys.stdout.write(begin)
	sys.stdout.write("{ \"")
	sys.stdout.write("\", \"".join(list).encode('ascii', 'ignore'))
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

specificitiesLength = 0
indexSpecificities = []
indexSpecificities.append(str(specificitiesLength))
specSites = []
specPositions = []
specClassifications = []

deltasLength = 0
indexDeltas = []
indexDeltas.append(str(deltasLength))
deltaSymbols = []
deltaNumbers = []

altNamesLength = 0
indexAltNames = []
indexAltNames.append(str(altNamesLength))
altNames = []

specNeutralLossDeltaLength = 0
indexSpecNeutralLoss = []
indexSpecNeutralLoss.append(str(specNeutralLossDeltaLength))
specNeutralLossLength = 0
indexSpecNeutralLossDeltas = []
indexSpecNeutralLossDeltas.append(str(specNeutralLossLength))
specNeutralLossSymbols = []
specNeutralLossNumbers = []

specPepNeutralLossDeltaLength = 0
indexSpecPepNeutralLoss = []
indexSpecPepNeutralLoss.append(str(specPepNeutralLossDeltaLength))
specPepNeutralLossLength = 0
indexSpecPepNeutralLossDeltas = []
indexSpecPepNeutralLossDeltas.append(str(specPepNeutralLossLength))
specPepNeutralLossSymbols = []
specPepNeutralLossNumbers = []

for parent in tree.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}mod"):
	titles.append(parent.attrib.get("title"))
	fullNames.append(parent.attrib.get("full_name"))
	iter = parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}specificity")
	specificitiesLength += len(list(iter))
	indexSpecificities.append(str(specificitiesLength))
	for specificity in iter:
		specSites.append(specificity.attrib.get("site"))
		specPositions.append(specificity.attrib.get("position"))
		specClassifications.append(specificity.attrib.get("classification"))
		iter = specificity.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}NeutralLoss")
		specNeutralLossDeltaLength += len(list(iter))
		indexSpecNeutralLoss.append(str(specNeutralLossDeltaLength))
		for neutralLoss in iter:
			iter = neutralLoss.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}element")
			specNeutralLossLength += len(list(iter))
			indexSpecNeutralLossDeltas.append(str(specNeutralLossLength))
			for element in iter:
				specNeutralLossSymbols.append(element.attrib.get("symbol"))
				specNeutralLossNumbers.append(element.attrib.get("number"))
		iter = specificity.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}PepNeutralLoss")
		specPepNeutralLossDeltaLength += len(list(iter))
		indexSpecPepNeutralLoss.append(str(specPepNeutralLossDeltaLength))
		for pepNeutralLoss in iter:
			iter = neutralLoss.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}element")
			specPepNeutralLossLength += len(list(iter))
			indexSpecPepNeutralLossDeltas.append(str(specPepNeutralLossLength))
			for element in iter:
				specPepNeutralLossSymbols.append(element.attrib.get("symbol"))
				specPepNeutralLossNumbers.append(element.attrib.get("number"))
	for delta in parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}delta"):
		iter = delta.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}element")
		deltasLength += len(list(iter))
		indexDeltas.append(str(deltasLength))
		for element in iter:
			deltaSymbols.append(element.attrib.get("symbol"))
			deltaNumbers.append(element.attrib.get("number"))
	iter = parent.getiterator("{http://www.unimod.org/xmlns/schema/unimod_2}alt_name")
	altNamesLength += len(list(iter))
	indexAltNames.append(str(altNamesLength))
	for altName in iter:
		altNames.append(altName.text)

sys.stdout.write("const libaas::Size nModifications = " + str(len(titles)) + ";\n")
printStringArray("const libaas::Char* titles[] = ", titles)

printStringArray("const libaas::Char* fullNames[] = ", fullNames)

printNumberArray("const libaas::Size indexSpecificities[] = ", indexSpecificities)
printSpecArrays("const libaas::Char* specificities[][3] = ", specSites, specPositions, specClassifications)

printNumberArray("const libaas::Size indexDeltas[] = ", indexDeltas)
printStringArray("const libaas::Char* deltaSymbols[] = ", deltaSymbols)
printNumberArray("const libaas::Double deltaNumbers[] = ", deltaNumbers)

printNumberArray("const libaas::Size indexSpecNeutralLoss[] = ", indexSpecNeutralLoss)
printNumberArray("const libaas::Size indexSpecNeutralLossDeltas[] = ", indexSpecNeutralLossDeltas)
printStringArray("const libaas::Char* specNeutralLossSymbols[] = ", specNeutralLossSymbols)
printNumberArray("const libaas::Double specNeutralLossNumbers[] = ", specNeutralLossNumbers)

printNumberArray("const libaas::Size indexSpecPepNeutralLoss[] = ", indexSpecPepNeutralLoss)
printNumberArray("const libaas::Size indexSpecPepNeutralLossDeltas[] = ", indexSpecPepNeutralLossDeltas)
printStringArray("const libaas::Char* specPepNeutralLossSymbols[] = ", specPepNeutralLossSymbols)
printNumberArray("const libaas::Double specPepNeutralLossNumbers[] = ", specPepNeutralLossNumbers)

printNumberArray("const libaas::Size indexAltNames[] = ", indexAltNames)
printStringArray("const libaas::Char* altNames[] = ", altNames)
