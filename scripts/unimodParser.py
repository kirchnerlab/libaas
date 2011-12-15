import elementtree.ElementTree as ET
import sys
import getopt

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

class Usage(Exception):
    def __init__(self, msg):
        self.msg = msg

def main(argv=None):
    if argv is None:
        argv = sys.argv
    try:
        try:
		opts, args = getopt.getopt(argv[1:], "hi:", ["help"])
        except getopt.error, msg:
             raise Usage(msg)

	filename = ""

	for c in opts:
		if (c[0] == "-i"):
			filename = c[1]

	if (filename == ""):
		raise Usage("Missing input file")

	output = 1

	tree = ET.parse(filename)

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

	modTag = "{http://www.unimod.org/xmlns/schema/unimod_2}mod"
	specificityTag = "{http://www.unimod.org/xmlns/schema/unimod_2}specificity"
	neutralLossTag = "{http://www.unimod.org/xmlns/schema/unimod_2}NeutralLoss"
	pepNeutralLossTag = "{http://www.unimod.org/xmlns/schema/unimod_2}PepNeutralLoss"
	elementTag = "{http://www.unimod.org/xmlns/schema/unimod_2}element"
	deltaTag = "{http://www.unimod.org/xmlns/schema/unimod_2}delta"
	altNameTag = "{http://www.unimod.org/xmlns/schema/unimod_2}alt_name"

	# iterate over all modifications
	for parent in tree.getiterator(modTag):
		titles.append(parent.attrib.get("title"))
		fullNames.append(parent.attrib.get("full_name"))
		iter = parent.getiterator(specificityTag)
		specificitiesLength += len(list(iter))
		indexSpecificities.append(str(specificitiesLength))
		# iterate over all specificities
		for specificity in iter:
			specSites.append(specificity.attrib.get("site"))
			specPositions.append(specificity.attrib.get("position"))
			specClassifications.append(specificity.attrib.get("classification"))
			iter = specificity.getiterator(neutralLossTag)
			specNeutralLossDeltaLength += len(list(iter))
			indexSpecNeutralLoss.append(str(specNeutralLossDeltaLength))
			# iterate over neutral loss tags
			for neutralLoss in iter:
				iter = neutralLoss.getiterator(elementTag)
				specNeutralLossLength += len(list(iter))
				indexSpecNeutralLossDeltas.append(str(specNeutralLossLength))
				for element in iter:
					specNeutralLossSymbols.append(element.attrib.get("symbol"))
					specNeutralLossNumbers.append(element.attrib.get("number"))
			iter = specificity.getiterator(pepNeutralLossTag)
			specPepNeutralLossDeltaLength += len(list(iter))
			indexSpecPepNeutralLoss.append(str(specPepNeutralLossDeltaLength))
			# iterate over pep neutral loss tags
			for pepNeutralLoss in iter:
				iter = neutralLoss.getiterator(elementTag)
				specPepNeutralLossLength += len(list(iter))
				indexSpecPepNeutralLossDeltas.append(str(specPepNeutralLossLength))
				for element in iter:
					specPepNeutralLossSymbols.append(element.attrib.get("symbol"))
					specPepNeutralLossNumbers.append(element.attrib.get("number"))
		# iterate over delta tags (this should be exactly 1)
		for delta in parent.getiterator(deltaTag):
			iter = delta.getiterator(elementTag)
			deltasLength += len(list(iter))
			indexDeltas.append(str(deltasLength))
			for element in iter:
				deltaSymbols.append(element.attrib.get("symbol"))
				deltaNumbers.append(element.attrib.get("number"))
		iter = parent.getiterator(altNameTag)
		altNamesLength += len(list(iter))
		indexAltNames.append(str(altNamesLength))
		# iterate over alternative name tags
		for altName in iter:
			altNames.append(altName.text)
	
	if (output == 1):
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

    except Usage, err:
        print >>sys.stderr, err.msg
	print >>sys.stderr, "Usage: unimodParser.py -i filename"
	print >>sys.stderr, "    -i\t\tfilename (unimod.xml)"
        print >>sys.stderr, "for help use --help"
        return 2

if __name__ == "__main__":
    sys.exit(main())


