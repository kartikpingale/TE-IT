# ASSIGNMENT 1
# Write a program to implement an address book with options given below:
# 	1. Create
#	2. View
#	3. Insert
#	4. Delete
#	5. Modify
#	6. Exit

createAddressBook()
{
	echo
	read -p "Enter no. of records: " n
	
	for((i=0; i<n; i++))
	do
		echo
		echo "Enter ID"
		read ID[i]
		echo "Enter name"
		read name[i]
		echo "Email"
		read email[i]
	done
}

displayRecords()
{
	echo
	echo "ID	NAME	EMAIL"
	for((i=0; i<n; i++))
	do
		echo "${ID[i]}	${name[i]}	${email[i]}"
	done
}

insertRecord()
{
	echo
	echo "Enter ID to insert"
	read ins_id
	
	for((i=0; i<n; i++))
	do
		if test "$ins_id" == "${ID[i]}"
		then
			echo
			echo "ID already exists"
			dup_id=1
		fi
	done
	
	if test "$dup_id" != 1
	then
		ID[n]=$ins_id
		echo "Enter name"
		read name[n]
		echo "Email"
		read email[n]
		n=$((n+1))
	fi
}

deleteRecord()
{
	echo
	echo "Enter index of record to delete"
	read del_pos
	
	for((i=del_pos; i<n-1; i++))
	do
		ID[i]=${ID[i+1]}
		name[i]=${name[i+1]}
		email[i]=${email[i+1]}
	done
	n=$((n-1))
}

modifyRecord()
{
	echo
	echo "Enter ID to modify"
	read mod_id
	is_mod=0
	
	for((i=0; i<n; i++))
	do
		if test "$mod_id" == "${ID[i]}"
		then
			echo "Enter name"
			read name[i]
			echo "Email"
			read email[i]
			is_mod=1
		fi
	done
	
	if test "$is_mod" == 0
	then
		echo
		echo "ID does not exist"
	fi
}

exitFunction()
{
	echo
	echo "Thank You!"
	echo
	break
}

createAddressBook

while :
do

	echo
	echo "ADDRESS BOOK"
	echo "1. View"
	echo "2. Insert"
	echo "3. Delete"
	echo "4. Modify"
	echo "5. Exit"
	echo
	
	echo "Enter choice"
	read choice

	if test "$choice" == 1
	then
		displayRecords
	fi

	if test "$choice" == 2
	then
		insertRecord
	fi

	if test "$choice" == 3
	then
		deleteRecord
	fi

	if test "$choice" == 4
	then
		modifyRecord
	fi

	if test "$choice" == 5
	then
		exitFunction
	fi

done